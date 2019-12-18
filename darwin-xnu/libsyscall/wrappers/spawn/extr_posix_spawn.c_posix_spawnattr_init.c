#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _posix_spawnattr {int dummy; } ;
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {int psa_priority; int psa_memlimit_active; int psa_memlimit_inactive; int psa_reserved; scalar_t__ psa_max_addr; int /*<<< orphan*/  psa_darwin_role; int /*<<< orphan*/  psa_qos_clamp; int /*<<< orphan*/ * psa_persona_info; int /*<<< orphan*/ * psa_coalition_info; int /*<<< orphan*/ * psa_mac_extensions; scalar_t__ psa_cpumonitor_interval; scalar_t__ psa_cpumonitor_percent; scalar_t__ psa_thread_limit; scalar_t__ psa_jetsam_flags; int /*<<< orphan*/  psa_apptype; scalar_t__ flags_padding; scalar_t__ short_padding; scalar_t__ psa_pcontrol; int /*<<< orphan*/ * psa_ports; int /*<<< orphan*/  psa_binprefs; scalar_t__ psa_pgroup; scalar_t__ psa_sigmask; scalar_t__ psa_sigdefault; scalar_t__ psa_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  POSIX_SPAWN_DARWIN_ROLE_NONE ; 
 int /*<<< orphan*/  POSIX_SPAWN_PROCESS_TYPE_DEFAULT ; 
 int /*<<< orphan*/  POSIX_SPAWN_PROC_CLAMP_NONE ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
posix_spawnattr_init(posix_spawnattr_t *attr)
{
	_posix_spawnattr_t *psattrp = (_posix_spawnattr_t *)attr;
	int	err = 0;

	if ((*psattrp = (_posix_spawnattr_t)malloc(sizeof(struct _posix_spawnattr))) == NULL) {
		err = ENOMEM;
	} else {

		/*
		 * The default value of this attribute shall be as if no
		 * flags were set
		 */
		(*psattrp)->psa_flags = 0;

		/*
		 * The default value of this attribute shall be an empty
		 * signal set
		 */
		(*psattrp)->psa_sigdefault = 0;

		/* The default value of this attribute is unspecified */
		(*psattrp)->psa_sigmask = 0;

		/* The default value of this attribute shall be zero */
		(*psattrp)->psa_pgroup = 0;	/* doesn't matter */

		/* Default is no binary preferences, i.e. use normal grading */
		memset((*psattrp)->psa_binprefs, 0, 
				sizeof((*psattrp)->psa_binprefs));

		/* Default is no port actions to take */
		(*psattrp)->psa_ports = NULL;

		/*
		 * The default value of this attribute shall be an no
		 * process control on resource starvation
		 */
		(*psattrp)->psa_pcontrol = 0;

		/*
		 * Initializing the alignment paddings. 
		 */

		 (*psattrp)->short_padding = 0; 
		 (*psattrp)->flags_padding = 0; 

		/* Default is no new apptype requested */
		(*psattrp)->psa_apptype = POSIX_SPAWN_PROCESS_TYPE_DEFAULT;

		/* Jetsam related */
		(*psattrp)->psa_jetsam_flags = 0;
		(*psattrp)->psa_priority = -1;
		(*psattrp)->psa_memlimit_active = -1;
		(*psattrp)->psa_memlimit_inactive = -1;

		/* Default is no thread limit */
		(*psattrp)->psa_thread_limit = 0;

		/* Default is no CPU usage monitor active. */
		(*psattrp)->psa_cpumonitor_percent = 0;
		(*psattrp)->psa_cpumonitor_interval = 0;

		/* Default is no MAC policy extensions. */
		(*psattrp)->psa_mac_extensions = NULL;

		/* Default is to inherit parent's coalition(s) */
		(*psattrp)->psa_coalition_info = NULL;

		(*psattrp)->psa_persona_info = NULL;

		/*
		 * old coalition field
		 * For backwards compatibility reasons, we set this to 1
		 * which is the first valid coalition id. This will allow
		 * newer user space code to properly spawn processes on
		 * older kernels
		 * (they will just all end up in the same coalition).
		 */
		(*psattrp)->psa_reserved = 1;

		/* Default is no new clamp */
		(*psattrp)->psa_qos_clamp = POSIX_SPAWN_PROC_CLAMP_NONE;

		/* Default is no change to role */
		(*psattrp)->psa_darwin_role = POSIX_SPAWN_DARWIN_ROLE_NONE;

		(*psattrp)->psa_max_addr = 0;
	}

	return (err);
}