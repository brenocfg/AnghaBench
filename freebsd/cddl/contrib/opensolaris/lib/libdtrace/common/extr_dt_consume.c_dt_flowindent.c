#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_14__ {char* dtpd_provider; char* dtpd_name; scalar_t__ dtpd_id; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
struct TYPE_15__ {char const* dtpda_prefix; scalar_t__ dtpda_indent; scalar_t__ dtpda_flow; TYPE_5__* dtpda_edesc; TYPE_2__* dtpda_pdesc; } ;
typedef  TYPE_3__ dtrace_probedata_t ;
struct TYPE_16__ {TYPE_1__** dt_pdesc; } ;
typedef  TYPE_4__ dtrace_hdl_t ;
typedef  scalar_t__ dtrace_flowkind_t ;
struct TYPE_17__ {size_t dtepd_epid; scalar_t__ dtepd_size; } ;
typedef  TYPE_5__ dtrace_eprobedesc_t ;
typedef  size_t dtrace_epid_t ;
struct TYPE_18__ {size_t dtbd_size; scalar_t__ dtbd_data; } ;
typedef  TYPE_6__ dtrace_bufdesc_t ;
struct TYPE_13__ {scalar_t__ dtpd_id; } ;

/* Variables and functions */
 scalar_t__ DTRACEFLOW_ENTRY ; 
 scalar_t__ DTRACEFLOW_NONE ; 
 scalar_t__ DTRACEFLOW_RETURN ; 
 size_t DTRACE_EPIDNONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int dt_epid_lookup (TYPE_4__*,size_t,TYPE_5__**,TYPE_2__**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

__attribute__((used)) static int
dt_flowindent(dtrace_hdl_t *dtp, dtrace_probedata_t *data, dtrace_epid_t last,
    dtrace_bufdesc_t *buf, size_t offs)
{
	dtrace_probedesc_t *pd = data->dtpda_pdesc, *npd;
	dtrace_eprobedesc_t *epd = data->dtpda_edesc, *nepd;
	char *p = pd->dtpd_provider, *n = pd->dtpd_name, *sub;
	dtrace_flowkind_t flow = DTRACEFLOW_NONE;
	const char *str = NULL;
	static const char *e_str[2] = { " -> ", " => " };
	static const char *r_str[2] = { " <- ", " <= " };
	static const char *ent = "entry", *ret = "return";
	static int entlen = 0, retlen = 0;
	dtrace_epid_t next, id = epd->dtepd_epid;
	int rval;

	if (entlen == 0) {
		assert(retlen == 0);
		entlen = strlen(ent);
		retlen = strlen(ret);
	}

	/*
	 * If the name of the probe is "entry" or ends with "-entry", we
	 * treat it as an entry; if it is "return" or ends with "-return",
	 * we treat it as a return.  (This allows application-provided probes
	 * like "method-entry" or "function-entry" to participate in flow
	 * indentation -- without accidentally misinterpreting popular probe
	 * names like "carpentry", "gentry" or "Coventry".)
	 */
	if ((sub = strstr(n, ent)) != NULL && sub[entlen] == '\0' &&
	    (sub == n || sub[-1] == '-')) {
		flow = DTRACEFLOW_ENTRY;
		str = e_str[strcmp(p, "syscall") == 0];
	} else if ((sub = strstr(n, ret)) != NULL && sub[retlen] == '\0' &&
	    (sub == n || sub[-1] == '-')) {
		flow = DTRACEFLOW_RETURN;
		str = r_str[strcmp(p, "syscall") == 0];
	}

	/*
	 * If we're going to indent this, we need to check the ID of our last
	 * call.  If we're looking at the same probe ID but a different EPID,
	 * we _don't_ want to indent.  (Yes, there are some minor holes in
	 * this scheme -- it's a heuristic.)
	 */
	if (flow == DTRACEFLOW_ENTRY) {
		if ((last != DTRACE_EPIDNONE && id != last &&
		    pd->dtpd_id == dtp->dt_pdesc[last]->dtpd_id))
			flow = DTRACEFLOW_NONE;
	}

	/*
	 * If we're going to unindent this, it's more difficult to see if
	 * we don't actually want to unindent it -- we need to look at the
	 * _next_ EPID.
	 */
	if (flow == DTRACEFLOW_RETURN) {
		offs += epd->dtepd_size;

		do {
			if (offs >= buf->dtbd_size)
				goto out;

			next = *(uint32_t *)((uintptr_t)buf->dtbd_data + offs);

			if (next == DTRACE_EPIDNONE)
				offs += sizeof (id);
		} while (next == DTRACE_EPIDNONE);

		if ((rval = dt_epid_lookup(dtp, next, &nepd, &npd)) != 0)
			return (rval);

		if (next != id && npd->dtpd_id == pd->dtpd_id)
			flow = DTRACEFLOW_NONE;
	}

out:
	if (flow == DTRACEFLOW_ENTRY || flow == DTRACEFLOW_RETURN) {
		data->dtpda_prefix = str;
	} else {
		data->dtpda_prefix = "| ";
	}

	if (flow == DTRACEFLOW_RETURN && data->dtpda_indent > 0)
		data->dtpda_indent -= 2;

	data->dtpda_flow = flow;

	return (0);
}