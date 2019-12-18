#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct module {scalar_t__ sdt_nprobes; TYPE_2__* sdt_probes; } ;
struct modctl {char* mod_modname; int /*<<< orphan*/  mod_loadcnt; scalar_t__ mod_address; } ;
struct TYPE_11__ {scalar_t__ sdtp_id; char* sdtp_prefix; int /*<<< orphan*/ * sdtp_name; } ;
typedef  TYPE_1__ sdt_provider_t ;
struct TYPE_12__ {char* sdpd_name; char* sdpd_func; scalar_t__ sdpd_offset; struct TYPE_12__* sdpd_next; } ;
typedef  TYPE_2__ sdt_probedesc_t ;
struct TYPE_13__ {char* sdp_name; int sdp_namelen; int sdp_id; int /*<<< orphan*/ * sdp_patchpoint; int /*<<< orphan*/  sdp_savedval; int /*<<< orphan*/  sdp_patchval; struct TYPE_13__* sdp_hashnext; struct TYPE_13__* sdp_next; TYPE_1__* sdp_provider; struct modctl* sdp_ctl; int /*<<< orphan*/  sdp_loadcnt; } ;
typedef  TYPE_3__ sdt_probe_t ;
typedef  int /*<<< orphan*/  sdt_instr_t ;
typedef  int dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DTRACE_IDNONE ; 
 scalar_t__ DTRACE_PROVNONE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 size_t SDT_ADDR2NDX (scalar_t__) ; 
 int /*<<< orphan*/  SDT_AFRAMES ; 
 int /*<<< orphan*/  SDT_PATCHVAL ; 
 TYPE_3__* dtrace_probe_arg (scalar_t__,int) ; 
 int dtrace_probe_create (scalar_t__,char*,char const*,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int dtrace_probe_lookup (scalar_t__,char*,char const*,char*) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,TYPE_2__*,TYPE_3__*,char*,int) ; 
 TYPE_3__** sdt_probetab ; 
 TYPE_1__* sdt_providers ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static void
__sdt_provide_module(void *arg, struct modctl *ctl)
{
#pragma unused(arg)
	struct module *mp = (struct module *)ctl->mod_address;
	char *modname = ctl->mod_modname;
	sdt_probedesc_t *sdpd;
	sdt_probe_t *sdp, *old;
	sdt_provider_t *prov;
	int len;

	/*
	 * One for all, and all for one:  if we haven't yet registered all of
	 * our providers, we'll refuse to provide anything.
	 */
	for (prov = sdt_providers; prov->sdtp_name != NULL; prov++) {
		if (prov->sdtp_id == DTRACE_PROVNONE)
			return;
	}

	if (!mp || mp->sdt_nprobes != 0 || (sdpd = mp->sdt_probes) == NULL)
		return;

	for (sdpd = mp->sdt_probes; sdpd != NULL; sdpd = sdpd->sdpd_next) {
	    const char *name = sdpd->sdpd_name, *func;
	    char *nname;
		int i, j;
		dtrace_id_t id;

		for (prov = sdt_providers; prov->sdtp_prefix != NULL; prov++) {
			const char *prefpart, *prefix = prov->sdtp_prefix;

			if ((prefpart = strstr(name, prefix))) {
				name = prefpart + strlen(prefix);
				break;
			}
		}

		nname = kmem_alloc(len = strlen(name) + 1, KM_SLEEP);

		for (i = 0, j = 0; name[j] != '\0'; i++) {
			if (name[j] == '_' && name[j + 1] == '_') {
				nname[i] = '-';
				j += 2;
			} else {
				nname[i] = name[j++];
			}
		}

		nname[i] = '\0';

		sdp = kmem_zalloc(sizeof (sdt_probe_t), KM_SLEEP);
		sdp->sdp_loadcnt = ctl->mod_loadcnt;
		sdp->sdp_ctl = ctl;
		sdp->sdp_name = nname;
		sdp->sdp_namelen = len;
		sdp->sdp_provider = prov;

		func = sdpd->sdpd_func;

		if (func == NULL)
			func = "<unknown>";

		/*
		 * We have our provider.  Now create the probe.
		 */
		if ((id = dtrace_probe_lookup(prov->sdtp_id, modname,
		    func, nname)) != DTRACE_IDNONE) {
			old = dtrace_probe_arg(prov->sdtp_id, id);
			ASSERT(old != NULL);

			sdp->sdp_next = old->sdp_next;
			sdp->sdp_id = id;
			old->sdp_next = sdp;
		} else {
			sdp->sdp_id = dtrace_probe_create(prov->sdtp_id,
			    modname, func, nname, SDT_AFRAMES, sdp);

			mp->sdt_nprobes++;
		}

#if 0		
		printf ("__sdt_provide_module:  sdpd=0x%p  sdp=0x%p  name=%s, id=%d\n", sdpd, sdp, nname, sdp->sdp_id);
#endif		

		sdp->sdp_hashnext =
		    sdt_probetab[SDT_ADDR2NDX(sdpd->sdpd_offset)];
		sdt_probetab[SDT_ADDR2NDX(sdpd->sdpd_offset)] = sdp;

		sdp->sdp_patchval = SDT_PATCHVAL;
		sdp->sdp_patchpoint = (sdt_instr_t *)sdpd->sdpd_offset;
		sdp->sdp_savedval = *sdp->sdp_patchpoint;
	}
}