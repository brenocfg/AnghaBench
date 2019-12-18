#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int user_addr_t ;
typedef  int u_long ;
struct proc {int dummy; } ;
struct pfr_table {char* anchor; size_t rs_num; int /*<<< orphan*/  ticket; int /*<<< orphan*/  pfrt_anchor; } ;
struct pfioc_trans_e {char* anchor; size_t rs_num; int /*<<< orphan*/  ticket; int /*<<< orphan*/  pfrt_anchor; } ;
struct pfioc_trans_64 {int esize; int size; int array; } ;
struct pfioc_trans_32 {int esize; int size; int array; } ;
struct pf_ruleset {TYPE_2__* rules; int /*<<< orphan*/  tticket; int /*<<< orphan*/  topen; } ;
struct TYPE_3__ {int /*<<< orphan*/  ticket; int /*<<< orphan*/  open; } ;
struct TYPE_4__ {TYPE_1__ inactive; } ;

/* Variables and functions */
#define  DIOCXBEGIN 132 
#define  DIOCXCOMMIT 131 
#define  DIOCXROLLBACK 130 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
#define  PF_RULESET_ALTQ 129 
 size_t PF_RULESET_MAX ; 
#define  PF_RULESET_TABLE 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FREE (struct pfr_table*,int /*<<< orphan*/ ) ; 
 struct pfr_table* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pfr_table*,int) ; 
 int /*<<< orphan*/  copyin (int,struct pfr_table*,int) ; 
 int /*<<< orphan*/  copyout (struct pfr_table*,int,int) ; 
 int pf_begin_rules (int /*<<< orphan*/ *,size_t,char*) ; 
 int pf_commit_rules (int /*<<< orphan*/ ,size_t,char*) ; 
 struct pf_ruleset* pf_find_ruleset (char*) ; 
 int pf_rollback_rules (int /*<<< orphan*/ ,size_t,char*) ; 
 int pfr_ina_begin (struct pfr_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pfr_ina_commit (struct pfr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pfr_ina_rollback (struct pfr_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int proc_is64bit (struct proc*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
pfioctl_ioc_trans(u_long cmd, struct pfioc_trans_32 *io32,
    struct pfioc_trans_64 *io64, struct proc *p)
{
	int p64 = proc_is64bit(p);
	int error = 0, esize, size;
	user_addr_t buf;

	esize = (p64 ? io64->esize : io32->esize);
	size = (p64 ? io64->size : io32->size);
	buf = (p64 ? io64->array : io32->array);

	switch (cmd) {
	case DIOCXBEGIN: {
		struct pfioc_trans_e	*ioe;
		struct pfr_table	*table;
		int			 i;

		if (esize != sizeof (*ioe)) {
			error = ENODEV;
			goto fail;
		}
		ioe = _MALLOC(sizeof (*ioe), M_TEMP, M_WAITOK);
		table = _MALLOC(sizeof (*table), M_TEMP, M_WAITOK);
		for (i = 0; i < size; i++, buf += sizeof (*ioe)) {
			if (copyin(buf, ioe, sizeof (*ioe))) {
				_FREE(table, M_TEMP);
				_FREE(ioe, M_TEMP);
				error = EFAULT;
				goto fail;
			}
			ioe->anchor[sizeof (ioe->anchor) - 1] = '\0';
			switch (ioe->rs_num) {
			case PF_RULESET_ALTQ:
				break;
			case PF_RULESET_TABLE:
				bzero(table, sizeof (*table));
				strlcpy(table->pfrt_anchor, ioe->anchor,
				    sizeof (table->pfrt_anchor));
				if ((error = pfr_ina_begin(table,
				    &ioe->ticket, NULL, 0))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail;
				}
				break;
			default:
				if ((error = pf_begin_rules(&ioe->ticket,
				    ioe->rs_num, ioe->anchor))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail;
				}
				break;
			}
			if (copyout(ioe, buf, sizeof (*ioe))) {
				_FREE(table, M_TEMP);
				_FREE(ioe, M_TEMP);
				error = EFAULT;
				goto fail;
			}
		}
		_FREE(table, M_TEMP);
		_FREE(ioe, M_TEMP);
		break;
	}

	case DIOCXROLLBACK: {
		struct pfioc_trans_e	*ioe;
		struct pfr_table	*table;
		int			 i;

		if (esize != sizeof (*ioe)) {
			error = ENODEV;
			goto fail;
		}
		ioe = _MALLOC(sizeof (*ioe), M_TEMP, M_WAITOK);
		table = _MALLOC(sizeof (*table), M_TEMP, M_WAITOK);
		for (i = 0; i < size; i++, buf += sizeof (*ioe)) {
			if (copyin(buf, ioe, sizeof (*ioe))) {
				_FREE(table, M_TEMP);
				_FREE(ioe, M_TEMP);
				error = EFAULT;
				goto fail;
			}
			ioe->anchor[sizeof (ioe->anchor) - 1] = '\0';
			switch (ioe->rs_num) {
			case PF_RULESET_ALTQ:
				break;
			case PF_RULESET_TABLE:
				bzero(table, sizeof (*table));
				strlcpy(table->pfrt_anchor, ioe->anchor,
				    sizeof (table->pfrt_anchor));
				if ((error = pfr_ina_rollback(table,
				    ioe->ticket, NULL, 0))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail; /* really bad */
				}
				break;
			default:
				if ((error = pf_rollback_rules(ioe->ticket,
				    ioe->rs_num, ioe->anchor))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail; /* really bad */
				}
				break;
			}
		}
		_FREE(table, M_TEMP);
		_FREE(ioe, M_TEMP);
		break;
	}

	case DIOCXCOMMIT: {
		struct pfioc_trans_e	*ioe;
		struct pfr_table	*table;
		struct pf_ruleset	*rs;
		user_addr_t		 _buf = buf;
		int			 i;

		if (esize != sizeof (*ioe)) {
			error = ENODEV;
			goto fail;
		}
		ioe = _MALLOC(sizeof (*ioe), M_TEMP, M_WAITOK);
		table = _MALLOC(sizeof (*table), M_TEMP, M_WAITOK);
		/* first makes sure everything will succeed */
		for (i = 0; i < size; i++, buf += sizeof (*ioe)) {
			if (copyin(buf, ioe, sizeof (*ioe))) {
				_FREE(table, M_TEMP);
				_FREE(ioe, M_TEMP);
				error = EFAULT;
				goto fail;
			}
			ioe->anchor[sizeof (ioe->anchor) - 1] = '\0';
			switch (ioe->rs_num) {
			case PF_RULESET_ALTQ:
				break;
			case PF_RULESET_TABLE:
				rs = pf_find_ruleset(ioe->anchor);
				if (rs == NULL || !rs->topen || ioe->ticket !=
				    rs->tticket) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					error = EBUSY;
					goto fail;
				}
				break;
			default:
				if (ioe->rs_num < 0 || ioe->rs_num >=
				    PF_RULESET_MAX) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					error = EINVAL;
					goto fail;
				}
				rs = pf_find_ruleset(ioe->anchor);
				if (rs == NULL ||
				    !rs->rules[ioe->rs_num].inactive.open ||
				    rs->rules[ioe->rs_num].inactive.ticket !=
				    ioe->ticket) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					error = EBUSY;
					goto fail;
				}
				break;
			}
		}
		buf = _buf;
		/* now do the commit - no errors should happen here */
		for (i = 0; i < size; i++, buf += sizeof (*ioe)) {
			if (copyin(buf, ioe, sizeof (*ioe))) {
				_FREE(table, M_TEMP);
				_FREE(ioe, M_TEMP);
				error = EFAULT;
				goto fail;
			}
			ioe->anchor[sizeof (ioe->anchor) - 1] = '\0';
			switch (ioe->rs_num) {
			case PF_RULESET_ALTQ:
				break;
			case PF_RULESET_TABLE:
				bzero(table, sizeof (*table));
				strlcpy(table->pfrt_anchor, ioe->anchor,
				    sizeof (table->pfrt_anchor));
				if ((error = pfr_ina_commit(table, ioe->ticket,
				    NULL, NULL, 0))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail; /* really bad */
				}
				break;
			default:
				if ((error = pf_commit_rules(ioe->ticket,
				    ioe->rs_num, ioe->anchor))) {
					_FREE(table, M_TEMP);
					_FREE(ioe, M_TEMP);
					goto fail; /* really bad */
				}
				break;
			}
		}
		_FREE(table, M_TEMP);
		_FREE(ioe, M_TEMP);
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
fail:
	return (error);
}