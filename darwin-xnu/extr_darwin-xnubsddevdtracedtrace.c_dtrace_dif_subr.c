#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_22__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_17__ ;

/* Type definitions */
typedef  uintptr_t user_addr_t ;
typedef  int uint_t ;
typedef  char uint8_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  tokmap ;
struct proc {int /*<<< orphan*/  p_pptr; int /*<<< orphan*/  p_pid; } ;
struct TYPE_26__ {int* _S6_u8; } ;
struct in6_addr {TYPE_2__ _S6_un; } ;
typedef  size_t pid_t ;
struct TYPE_24__ {int /*<<< orphan*/  m_spinlock; } ;
struct TYPE_27__ {TYPE_1__ m_spin; } ;
typedef  TYPE_3__ mutex_impl_t ;
typedef  int /*<<< orphan*/  krwlock_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  ipaddr_t ;
typedef  size_t int64_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_28__ {size_t* dts_options; int /*<<< orphan*/  dts_vstate; } ;
typedef  TYPE_4__ dtrace_state_t ;
struct TYPE_29__ {size_t dtms_scratch_ptr; uintptr_t dtms_strtok; uintptr_t dtms_strtok_limit; } ;
typedef  TYPE_5__ dtrace_mstate_t ;
struct TYPE_30__ {uintptr_t dttk_value; } ;
typedef  TYPE_6__ dtrace_key_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_25__ {size_t cpu_id; } ;
struct TYPE_23__ {int cpuc_dtrace_flags; size_t cpuc_dtrace_illval; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_22__* CPU ; 
 int volatile CPU_DTRACE_BADADDR ; 
 int volatile CPU_DTRACE_FAULT ; 
 int volatile CPU_DTRACE_ILLOP ; 
 int volatile CPU_DTRACE_KPRIV ; 
 int volatile CPU_DTRACE_NOFAULT ; 
 int volatile CPU_DTRACE_NOSCRATCH ; 
#define  DIF_SUBR_ALLOCA 173 
#define  DIF_SUBR_BASENAME 172 
#define  DIF_SUBR_BCOPY 171 
#define  DIF_SUBR_CLEANPATH 170 
#define  DIF_SUBR_COPYIN 169 
#define  DIF_SUBR_COPYINSTR 168 
#define  DIF_SUBR_COPYINTO 167 
#define  DIF_SUBR_COPYOUT 166 
#define  DIF_SUBR_COPYOUTSTR 165 
#define  DIF_SUBR_DDI_PATHNAME 164 
#define  DIF_SUBR_DIRNAME 163 
#define  DIF_SUBR_GETMAJOR 162 
#define  DIF_SUBR_GETMINOR 161 
#define  DIF_SUBR_HTONL 160 
#define  DIF_SUBR_HTONLL 159 
#define  DIF_SUBR_HTONS 158 
#define  DIF_SUBR_INDEX 157 
#define  DIF_SUBR_INET_NTOA 156 
#define  DIF_SUBR_INET_NTOA6 155 
#define  DIF_SUBR_INET_NTOP 154 
#define  DIF_SUBR_LLTOSTR 153 
#define  DIF_SUBR_MSGDSIZE 152 
#define  DIF_SUBR_MSGSIZE 151 
#define  DIF_SUBR_MUTEX_OWNED 150 
#define  DIF_SUBR_MUTEX_OWNER 149 
#define  DIF_SUBR_MUTEX_TYPE_ADAPTIVE 148 
#define  DIF_SUBR_MUTEX_TYPE_SPIN 147 
#define  DIF_SUBR_NTOHL 146 
#define  DIF_SUBR_NTOHLL 145 
#define  DIF_SUBR_NTOHS 144 
#define  DIF_SUBR_PROGENYOF 143 
#define  DIF_SUBR_RAND 142 
#define  DIF_SUBR_RINDEX 141 
#define  DIF_SUBR_RW_ISWRITER 140 
#define  DIF_SUBR_RW_READ_HELD 139 
#define  DIF_SUBR_RW_WRITE_HELD 138 
#define  DIF_SUBR_SPECULATION 137 
#define  DIF_SUBR_STRCHR 136 
#define  DIF_SUBR_STRJOIN 135 
#define  DIF_SUBR_STRLEN 134 
#define  DIF_SUBR_STRRCHR 133 
#define  DIF_SUBR_STRSTR 132 
#define  DIF_SUBR_STRTOK 131 
#define  DIF_SUBR_SUBSTR 130 
#define  DIF_SUBR_TOLOWER 129 
#define  DIF_SUBR_TOUPPER 128 
 size_t DTRACEOPT_STRSIZE ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int volatile) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int volatile) ; 
 int /*<<< orphan*/  DTRACE_INSCRATCH (TYPE_5__*,size_t) ; 
 scalar_t__ DTRACE_V4MAPPED_OFFSET ; 
 size_t DT_BSWAP_16 (int) ; 
 size_t DT_BSWAP_32 (int /*<<< orphan*/ ) ; 
 size_t DT_BSWAP_64 (size_t) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4COMPAT (struct in6_addr*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 size_t INET6_ADDRSTRLEN ; 
 size_t INET_ADDRSTRLEN ; 
 size_t LOCK_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MUTEX_NO_OWNER ; 
 int /*<<< orphan*/  MUTEX_OWNER (TYPE_3__*) ; 
 size_t MUTEX_TYPE_ADAPTIVE (TYPE_3__*) ; 
 size_t MUTEX_TYPE_SPIN (TYPE_3__*) ; 
 uintptr_t P2ROUNDUP (size_t,int) ; 
 size_t _RW_ISWRITER (int /*<<< orphan*/ *) ; 
 size_t _RW_READ_HELD (int /*<<< orphan*/ *,uintptr_t) ; 
 size_t _RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 TYPE_17__* cpu_core ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  dtrace_bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  dtrace_canload (uintptr_t,size_t,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_copyin (size_t,uintptr_t,size_t,int volatile*) ; 
 int /*<<< orphan*/  dtrace_copyinstr (size_t,uintptr_t,size_t,int volatile*) ; 
 int /*<<< orphan*/  dtrace_copyout (uintptr_t,uintptr_t,size_t,int volatile*) ; 
 int /*<<< orphan*/  dtrace_copyoutstr (uintptr_t,uintptr_t,size_t,int volatile*) ; 
 int /*<<< orphan*/  dtrace_destructive_disallow ; 
 int dtrace_gethrtime () ; 
 int /*<<< orphan*/  dtrace_inscratch (uintptr_t,size_t,TYPE_5__*) ; 
 int /*<<< orphan*/  dtrace_istoxic (uintptr_t,size_t) ; 
 int /*<<< orphan*/  dtrace_load32 (uintptr_t) ; 
 void* dtrace_load64 (uintptr_t) ; 
 char dtrace_load8 (uintptr_t) ; 
 void* dtrace_loadptr (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_priv_kernel (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_priv_proc (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_priv_proc_control (TYPE_4__*) ; 
 size_t dtrace_speculation (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_strcanload (uintptr_t,size_t,size_t*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 void* dtrace_strlen (char*,size_t) ; 
 int /*<<< orphan*/  dtrace_strncmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int nprocs ; 

__attribute__((used)) static void
dtrace_dif_subr(uint_t subr, uint_t rd, uint64_t *regs,
    dtrace_key_t *tupregs, int nargs,
    dtrace_mstate_t *mstate, dtrace_state_t *state)
{
	volatile uint16_t *flags = &cpu_core[CPU->cpu_id].cpuc_dtrace_flags;
	volatile uint64_t *illval = &cpu_core[CPU->cpu_id].cpuc_dtrace_illval;
	dtrace_vstate_t *vstate = &state->dts_vstate;

#if !defined(__APPLE__)
	union {
		mutex_impl_t mi;
		uint64_t mx;
	} m;

	union {
		krwlock_t ri;
		uintptr_t rw;
	} r;
#else
/* FIXME: awaits lock/mutex work */
#endif /* __APPLE__ */

	switch (subr) {
	case DIF_SUBR_RAND:
		regs[rd] = (dtrace_gethrtime() * 2416 + 374441) % 1771875;
		break;

#if !defined(__APPLE__)
	case DIF_SUBR_MUTEX_OWNED:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (kmutex_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		m.mx = dtrace_load64(tupregs[0].dttk_value);
		if (MUTEX_TYPE_ADAPTIVE(&m.mi))
			regs[rd] = MUTEX_OWNER(&m.mi) != MUTEX_NO_OWNER;
		else
			regs[rd] = LOCK_HELD(&m.mi.m_spin.m_spinlock);
		break;

	case DIF_SUBR_MUTEX_OWNER:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (kmutex_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		m.mx = dtrace_load64(tupregs[0].dttk_value);
		if (MUTEX_TYPE_ADAPTIVE(&m.mi) &&
		    MUTEX_OWNER(&m.mi) != MUTEX_NO_OWNER)
			regs[rd] = (uintptr_t)MUTEX_OWNER(&m.mi);
		else
			regs[rd] = 0;
		break;

	case DIF_SUBR_MUTEX_TYPE_ADAPTIVE:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (kmutex_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		m.mx = dtrace_load64(tupregs[0].dttk_value);
		regs[rd] = MUTEX_TYPE_ADAPTIVE(&m.mi);
		break;

	case DIF_SUBR_MUTEX_TYPE_SPIN:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (kmutex_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		m.mx = dtrace_load64(tupregs[0].dttk_value);
		regs[rd] = MUTEX_TYPE_SPIN(&m.mi);
		break;

	case DIF_SUBR_RW_READ_HELD: {
		uintptr_t tmp;

		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (uintptr_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		r.rw = dtrace_loadptr(tupregs[0].dttk_value);
		regs[rd] = _RW_READ_HELD(&r.ri, tmp);
		break;
	}

	case DIF_SUBR_RW_WRITE_HELD:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (krwlock_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		r.rw = dtrace_loadptr(tupregs[0].dttk_value);
		regs[rd] = _RW_WRITE_HELD(&r.ri);
		break;

	case DIF_SUBR_RW_ISWRITER:
		if (!dtrace_canload(tupregs[0].dttk_value, sizeof (krwlock_t),
		    mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		r.rw = dtrace_loadptr(tupregs[0].dttk_value);
		regs[rd] = _RW_ISWRITER(&r.ri);
		break;
#else
/* FIXME: awaits lock/mutex work */
#endif /* __APPLE__ */

	case DIF_SUBR_BCOPY: {
		/*
		 * We need to be sure that the destination is in the scratch
		 * region -- no other region is allowed.
		 */
		uintptr_t src = tupregs[0].dttk_value;
		uintptr_t dest = tupregs[1].dttk_value;
		size_t size = tupregs[2].dttk_value;

		if (!dtrace_inscratch(dest, size, mstate)) {
			*flags |= CPU_DTRACE_BADADDR;
			*illval = regs[rd];
			break;
		}

		if (!dtrace_canload(src, size, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		dtrace_bcopy((void *)src, (void *)dest, size);
		break;
	}

	case DIF_SUBR_ALLOCA:
	case DIF_SUBR_COPYIN: {
		uintptr_t dest = P2ROUNDUP(mstate->dtms_scratch_ptr, 8);
		uint64_t size =
		    tupregs[subr == DIF_SUBR_ALLOCA ? 0 : 1].dttk_value;
		size_t scratch_size = (dest - mstate->dtms_scratch_ptr) + size;

		/*
		 * Check whether the user can access kernel memory
		 */
		if (dtrace_priv_kernel(state) == 0) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_KPRIV);
			regs[rd] = 0;
			break;
		}
		/*
		 * This action doesn't require any credential checks since
		 * probes will not activate in user contexts to which the
		 * enabling user does not have permissions.
		 */

		/*
		 * Rounding up the user allocation size could have overflowed
		 * a large, bogus allocation (like -1ULL) to 0.
		 */
		if (scratch_size < size ||
		    !DTRACE_INSCRATCH(mstate, scratch_size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		if (subr == DIF_SUBR_COPYIN) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
			if (dtrace_priv_proc(state))
				dtrace_copyin(tupregs[0].dttk_value, dest, size, flags);
			DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
		}

		mstate->dtms_scratch_ptr += scratch_size;
		regs[rd] = dest;
		break;
	}

	case DIF_SUBR_COPYINTO: {
		uint64_t size = tupregs[1].dttk_value;
		uintptr_t dest = tupregs[2].dttk_value;

		/*
		 * This action doesn't require any credential checks since
		 * probes will not activate in user contexts to which the
		 * enabling user does not have permissions.
		 */
		if (!dtrace_inscratch(dest, size, mstate)) {
			*flags |= CPU_DTRACE_BADADDR;
			*illval = regs[rd];
			break;
		}

		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
		if (dtrace_priv_proc(state))
			dtrace_copyin(tupregs[0].dttk_value, dest, size, flags);
		DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
		break;
	}

	case DIF_SUBR_COPYINSTR: {
		uintptr_t dest = mstate->dtms_scratch_ptr;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];

		if (nargs > 1 && tupregs[1].dttk_value < size)
			size = tupregs[1].dttk_value + 1;

		/*
		 * This action doesn't require any credential checks since
		 * probes will not activate in user contexts to which the
		 * enabling user does not have permissions.
		 */
		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
		if (dtrace_priv_proc(state))
			dtrace_copyinstr(tupregs[0].dttk_value, dest, size, flags);
		DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);

		((char *)dest)[size - 1] = '\0';
		mstate->dtms_scratch_ptr += size;
		regs[rd] = dest;
		break;
	}

	case DIF_SUBR_MSGSIZE:
	case DIF_SUBR_MSGDSIZE: {
		/* Darwin does not implement SysV streams messages */
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		regs[rd] = 0;
		break;
	}

	case DIF_SUBR_PROGENYOF: {
		pid_t pid = tupregs[0].dttk_value;
		struct proc *p = current_proc();
		int rval = 0, lim = nprocs;

		while(p && (lim-- > 0)) {
			pid_t ppid;

			ppid = (pid_t)dtrace_load32((uintptr_t)&(p->p_pid));
			if (*flags & CPU_DTRACE_FAULT)
				break;

			if (ppid == pid) {
				rval = 1;
				break;
			}

			if (ppid == 0)
				break; /* Can't climb process tree any further. */

			p = (struct proc *)dtrace_loadptr((uintptr_t)&(p->p_pptr));
			if (*flags & CPU_DTRACE_FAULT)
				break;
		}

		regs[rd] = rval;
		break;
	}

	case DIF_SUBR_SPECULATION:
		regs[rd] = dtrace_speculation(state);
		break;


	case DIF_SUBR_COPYOUT: {
		uintptr_t kaddr = tupregs[0].dttk_value;
		user_addr_t uaddr = tupregs[1].dttk_value;
		uint64_t size = tupregs[2].dttk_value;

		if (!dtrace_destructive_disallow &&
		    dtrace_priv_proc_control(state) &&
		    !dtrace_istoxic(kaddr, size) &&
		    dtrace_canload(kaddr, size, mstate, vstate)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
			dtrace_copyout(kaddr, uaddr, size, flags);
			DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
		}
		break;
	}

	case DIF_SUBR_COPYOUTSTR: {
		uintptr_t kaddr = tupregs[0].dttk_value;
		user_addr_t uaddr = tupregs[1].dttk_value;
		uint64_t size = tupregs[2].dttk_value;
		size_t lim;

		if (!dtrace_destructive_disallow &&
		    dtrace_priv_proc_control(state) &&
		    !dtrace_istoxic(kaddr, size) &&
		    dtrace_strcanload(kaddr, size, &lim, mstate, vstate)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
			dtrace_copyoutstr(kaddr, uaddr, lim, flags);
			DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);
		}
		break;
	}

	case DIF_SUBR_STRLEN: {
		size_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uintptr_t addr = (uintptr_t)tupregs[0].dttk_value;
		size_t lim;

		if (!dtrace_strcanload(addr, size, &lim, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		regs[rd] = dtrace_strlen((char *)addr, lim);

		break;
	}

	case DIF_SUBR_STRCHR:
	case DIF_SUBR_STRRCHR: {
		/*
		 * We're going to iterate over the string looking for the
		 * specified character.  We will iterate until we have reached
		 * the string length or we have found the character.  If this
		 * is DIF_SUBR_STRRCHR, we will look for the last occurrence
		 * of the specified character instead of the first.
		 */
		uintptr_t addr = tupregs[0].dttk_value;
		uintptr_t addr_limit;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		size_t lim;
		char c, target = (char)tupregs[1].dttk_value;

		if (!dtrace_strcanload(addr, size, &lim, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}
		addr_limit = addr + lim;

		for (regs[rd] = 0; addr < addr_limit; addr++) {
			if ((c = dtrace_load8(addr)) == target) {
				regs[rd] = addr;

				if (subr == DIF_SUBR_STRCHR)
					break;
			}

			if (c == '\0')
				break;
		}

		break;
	}

	case DIF_SUBR_STRSTR:
	case DIF_SUBR_INDEX:
	case DIF_SUBR_RINDEX: {
		/*
		 * We're going to iterate over the string looking for the
		 * specified string.  We will iterate until we have reached
		 * the string length or we have found the string.  (Yes, this
		 * is done in the most naive way possible -- but considering
		 * that the string we're searching for is likely to be
		 * relatively short, the complexity of Rabin-Karp or similar
		 * hardly seems merited.)
		 */
		char *addr = (char *)(uintptr_t)tupregs[0].dttk_value;
		char *substr = (char *)(uintptr_t)tupregs[1].dttk_value;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		size_t len = dtrace_strlen(addr, size);
		size_t sublen = dtrace_strlen(substr, size);
		char *limit = addr + len, *orig = addr;
		int notfound = subr == DIF_SUBR_STRSTR ? 0 : -1;
		int inc = 1;

		regs[rd] = notfound;

		if (!dtrace_canload((uintptr_t)addr, len + 1, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!dtrace_canload((uintptr_t)substr, sublen + 1, mstate,
		    vstate)) {
			regs[rd] = 0;
			break;
		}

		/*
		 * strstr() and index()/rindex() have similar semantics if
		 * both strings are the empty string: strstr() returns a
		 * pointer to the (empty) string, and index() and rindex()
		 * both return index 0 (regardless of any position argument).
		 */
		if (sublen == 0 && len == 0) {
			if (subr == DIF_SUBR_STRSTR)
				regs[rd] = (uintptr_t)addr;
			else
				regs[rd] = 0;
			break;
		}

		if (subr != DIF_SUBR_STRSTR) {
			if (subr == DIF_SUBR_RINDEX) {
				limit = orig - 1;
				addr += len;
				inc = -1;
			}

			/*
			 * Both index() and rindex() take an optional position
			 * argument that denotes the starting position.
			 */
			if (nargs == 3) {
				int64_t pos = (int64_t)tupregs[2].dttk_value;

				/*
				 * If the position argument to index() is
				 * negative, Perl implicitly clamps it at
				 * zero.  This semantic is a little surprising
				 * given the special meaning of negative
				 * positions to similar Perl functions like
				 * substr(), but it appears to reflect a
				 * notion that index() can start from a
				 * negative index and increment its way up to
				 * the string.  Given this notion, Perl's
				 * rindex() is at least self-consistent in
				 * that it implicitly clamps positions greater
				 * than the string length to be the string
				 * length.  Where Perl completely loses
				 * coherence, however, is when the specified
				 * substring is the empty string ("").  In
				 * this case, even if the position is
				 * negative, rindex() returns 0 -- and even if
				 * the position is greater than the length,
				 * index() returns the string length.  These
				 * semantics violate the notion that index()
				 * should never return a value less than the
				 * specified position and that rindex() should
				 * never return a value greater than the
				 * specified position.  (One assumes that
				 * these semantics are artifacts of Perl's
				 * implementation and not the results of
				 * deliberate design -- it beggars belief that
				 * even Larry Wall could desire such oddness.)
				 * While in the abstract one would wish for
				 * consistent position semantics across
				 * substr(), index() and rindex() -- or at the
				 * very least self-consistent position
				 * semantics for index() and rindex() -- we
				 * instead opt to keep with the extant Perl
				 * semantics, in all their broken glory.  (Do
				 * we have more desire to maintain Perl's
				 * semantics than Perl does?  Probably.)
				 */
				if (subr == DIF_SUBR_RINDEX) {
					if (pos < 0) {
						if (sublen == 0)
							regs[rd] = 0;
						break;
					}

					if ((size_t)pos > len)
						pos = len;
				} else {
					if (pos < 0)
						pos = 0;

					if ((size_t)pos >= len) {
						if (sublen == 0)
							regs[rd] = len;
						break;
					}
				}

				addr = orig + pos;
			}
		}

		for (regs[rd] = notfound; addr != limit; addr += inc) {
			if (dtrace_strncmp(addr, substr, sublen) == 0) {
				if (subr != DIF_SUBR_STRSTR) {
					/*
					 * As D index() and rindex() are
					 * modeled on Perl (and not on awk),
					 * we return a zero-based (and not a
					 * one-based) index.  (For you Perl
					 * weenies: no, we're not going to add
					 * $[ -- and shouldn't you be at a con
					 * or something?)
					 */
					regs[rd] = (uintptr_t)(addr - orig);
					break;
				}

				ASSERT(subr == DIF_SUBR_STRSTR);
				regs[rd] = (uintptr_t)addr;
				break;
			}
		}

		break;
	}

	case DIF_SUBR_STRTOK: {
		uintptr_t addr = tupregs[0].dttk_value;
		uintptr_t tokaddr = tupregs[1].dttk_value;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uintptr_t limit, toklimit;
		size_t clim;
		char *dest = (char *)mstate->dtms_scratch_ptr;
		uint8_t c='\0', tokmap[32];	 /* 256 / 8 */
		uint64_t i = 0;

		/*
		 * Check both the token buffer and (later) the input buffer,
		 * since both could be non-scratch addresses.
		 */
		if (!dtrace_strcanload(tokaddr, size, &clim, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}
		toklimit = tokaddr + clim;

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		if (addr == 0) {
			/*
			 * If the address specified is NULL, we use our saved
			 * strtok pointer from the mstate.  Note that this
			 * means that the saved strtok pointer is _only_
			 * valid within multiple enablings of the same probe --
			 * it behaves like an implicit clause-local variable.
			 */
			addr = mstate->dtms_strtok;
			limit = mstate->dtms_strtok_limit;
		} else {
			/*
			 * If the user-specified address is non-NULL we must
			 * access check it.  This is the only time we have
			 * a chance to do so, since this address may reside
			 * in the string table of this clause-- future calls
			 * (when we fetch addr from mstate->dtms_strtok)
			 * would fail this access check.
			 */
			if (!dtrace_strcanload(addr, size, &clim, mstate,
				vstate)) {
				regs[rd] = 0;
				break;
			}
			limit = addr + clim;
		}

		/*
		 * First, zero the token map, and then process the token
		 * string -- setting a bit in the map for every character
		 * found in the token string.
		 */
		for (i = 0; i < (int)sizeof (tokmap); i++)
			tokmap[i] = 0;

		for (; tokaddr < toklimit; tokaddr++) {
			if ((c = dtrace_load8(tokaddr)) == '\0')
				break;

			ASSERT((c >> 3) < sizeof (tokmap));
			tokmap[c >> 3] |= (1 << (c & 0x7));
		}

		for (; addr < limit; addr++) {
			/*
			 * We're looking for a character that is _not_
			 * contained in the token string.
			 */
			if ((c = dtrace_load8(addr)) == '\0')
				break;

			if (!(tokmap[c >> 3] & (1 << (c & 0x7))))
				break;
		}

		if (c == '\0') {
			/*
			 * We reached the end of the string without finding
			 * any character that was not in the token string.
			 * We return NULL in this case, and we set the saved
			 * address to NULL as well.
			 */
			regs[rd] = 0;
			mstate->dtms_strtok = 0;
			mstate->dtms_strtok_limit = 0;
			break;
		}

		/*
		 * From here on, we're copying into the destination string.
		 */
		for (i = 0; addr < limit && i < size - 1; addr++) {
			if ((c = dtrace_load8(addr)) == '\0')
				break;

			if (tokmap[c >> 3] & (1 << (c & 0x7)))
				break;

			ASSERT(i < size);
			dest[i++] = c;
		}

		ASSERT(i < size);
		dest[i] = '\0';
		regs[rd] = (uintptr_t)dest;
		mstate->dtms_scratch_ptr += size;
		mstate->dtms_strtok = addr;
		mstate->dtms_strtok_limit = limit;
		break;
	}

	case DIF_SUBR_SUBSTR: {
		uintptr_t s = tupregs[0].dttk_value;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		char *d = (char *)mstate->dtms_scratch_ptr;
		int64_t index = (int64_t)tupregs[1].dttk_value;
		int64_t remaining = (int64_t)tupregs[2].dttk_value;
		size_t len = dtrace_strlen((char *)s, size);
		int64_t i = 0;

		if (!dtrace_canload(s, len + 1, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		if (nargs <= 2)
			remaining = (int64_t)size;

		if (index < 0) {
			index += len;

			if (index < 0 && index + remaining > 0) {
				remaining += index;
				index = 0;
			}
		}

		if ((size_t)index >= len || index < 0) {
			remaining = 0;
		} else if (remaining < 0) {
			remaining += len - index;
		} else if ((uint64_t)index + (uint64_t)remaining > size) {
			remaining = size - index;
		}

		for (i = 0; i < remaining; i++) {
			if ((d[i] = dtrace_load8(s + index + i)) == '\0')
				break;
			}

		d[i] = '\0';

		mstate->dtms_scratch_ptr += size;
		regs[rd] = (uintptr_t)d;
		break;
	}

	case DIF_SUBR_GETMAJOR:
		regs[rd] = (uintptr_t)major( (dev_t)tupregs[0].dttk_value );
		break;

	case DIF_SUBR_GETMINOR:
		regs[rd] = (uintptr_t)minor( (dev_t)tupregs[0].dttk_value );
		break;

	case DIF_SUBR_DDI_PATHNAME: {
		/* APPLE NOTE: currently unsupported on Darwin */
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		regs[rd] = 0;
		break;
	}

	case DIF_SUBR_STRJOIN: {
		char *d = (char *)mstate->dtms_scratch_ptr;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uintptr_t s1 = tupregs[0].dttk_value;
		uintptr_t s2 = tupregs[1].dttk_value;
		uint64_t i = 0, j = 0;
		size_t lim1, lim2;
		char c;

		if (!dtrace_strcanload(s1, size, &lim1, mstate, vstate) ||
		    !dtrace_strcanload(s2, size, &lim2, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		for (;;) {
			if (i >= size) {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
				regs[rd] = 0;
				break;
			}
			c = (i >= lim1) ? '\0' : dtrace_load8(s1++);
			if ((d[i++] = c) == '\0') {
				i--;
				break;
			}
		}

		for (;;) {
			if (i >= size) {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
				regs[rd] = 0;
				break;
			}
			c = (j++ >= lim2) ? '\0' : dtrace_load8(s2++);
			if ((d[i++] = c) == '\0')
				break;
		}

		if (i < size) {
			mstate->dtms_scratch_ptr += i;
			regs[rd] = (uintptr_t)d;
		}

		break;
	}

	case DIF_SUBR_LLTOSTR: {
		int64_t i = (int64_t)tupregs[0].dttk_value;
		uint64_t val, digit;
		uint64_t size = 65;	/* enough room for 2^64 in binary */
		char *end = (char *)mstate->dtms_scratch_ptr + size - 1;
		int base = 10;

		if (nargs > 1) {
			if ((base = tupregs[1].dttk_value) <= 1 ||
			     base > ('z' - 'a' + 1) + ('9' - '0' + 1)) {
				*flags |= CPU_DTRACE_ILLOP;
				break;
			}
		}

		val = (base == 10 && i < 0) ? i * -1 : i;

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		for (*end-- = '\0'; val; val /= base) {
			if ((digit = val % base) <= '9' - '0') {
				*end-- = '0' + digit;
			} else {
				*end-- = 'a' + (digit - ('9' - '0') - 1);
			}
		}

		if (i == 0 && base == 16)
			*end-- = '0';

		if (base == 16)
			*end-- = 'x';

		if (i == 0 || base == 8 || base == 16)
			*end-- = '0';

		if (i < 0 && base == 10)
			*end-- = '-';

		regs[rd] = (uintptr_t)end + 1;
		mstate->dtms_scratch_ptr += size;
		break;
	}

	case DIF_SUBR_HTONS:
	case DIF_SUBR_NTOHS:
#ifdef _BIG_ENDIAN
		regs[rd] = (uint16_t)tupregs[0].dttk_value;
#else
		regs[rd] = DT_BSWAP_16((uint16_t)tupregs[0].dttk_value);
#endif
		break;


	case DIF_SUBR_HTONL:
	case DIF_SUBR_NTOHL:
#ifdef _BIG_ENDIAN
		regs[rd] = (uint32_t)tupregs[0].dttk_value;
#else
		regs[rd] = DT_BSWAP_32((uint32_t)tupregs[0].dttk_value);
#endif
		break;


	case DIF_SUBR_HTONLL:
	case DIF_SUBR_NTOHLL:
#ifdef _BIG_ENDIAN
		regs[rd] = (uint64_t)tupregs[0].dttk_value;
#else
		regs[rd] = DT_BSWAP_64((uint64_t)tupregs[0].dttk_value);
#endif
		break;


	case DIF_SUBR_DIRNAME:
	case DIF_SUBR_BASENAME: {
		char *dest = (char *)mstate->dtms_scratch_ptr;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uintptr_t src = tupregs[0].dttk_value;
		int i, j, len = dtrace_strlen((char *)src, size);
		int lastbase = -1, firstbase = -1, lastdir = -1;
		int start, end;

		if (!dtrace_canload(src, len + 1, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		/*
		 * The basename and dirname for a zero-length string is
		 * defined to be "."
		 */
		if (len == 0) {
			len = 1;
			src = (uintptr_t)".";
		}

		/*
		 * Start from the back of the string, moving back toward the
		 * front until we see a character that isn't a slash.  That
		 * character is the last character in the basename.
		 */
		for (i = len - 1; i >= 0; i--) {
			if (dtrace_load8(src + i) != '/')
				break;
		}

		if (i >= 0)
			lastbase = i;

		/*
		 * Starting from the last character in the basename, move
		 * towards the front until we find a slash.  The character
		 * that we processed immediately before that is the first
		 * character in the basename.
		 */
		for (; i >= 0; i--) {
			if (dtrace_load8(src + i) == '/')
				break;
		}

		if (i >= 0)
			firstbase = i + 1;

		/*
		 * Now keep going until we find a non-slash character.  That
		 * character is the last character in the dirname.
		 */
		for (; i >= 0; i--) {
			if (dtrace_load8(src + i) != '/')
				break;
		}

		if (i >= 0)
			lastdir = i;

		ASSERT(!(lastbase == -1 && firstbase != -1));
		ASSERT(!(firstbase == -1 && lastdir != -1));

		if (lastbase == -1) {
			/*
			 * We didn't find a non-slash character.  We know that
			 * the length is non-zero, so the whole string must be
			 * slashes.  In either the dirname or the basename
			 * case, we return '/'.
			 */
			ASSERT(firstbase == -1);
			firstbase = lastbase = lastdir = 0;
		}

		if (firstbase == -1) {
			/*
			 * The entire string consists only of a basename
			 * component.  If we're looking for dirname, we need
			 * to change our string to be just "."; if we're
			 * looking for a basename, we'll just set the first
			 * character of the basename to be 0.
			 */
			if (subr == DIF_SUBR_DIRNAME) {
				ASSERT(lastdir == -1);
				src = (uintptr_t)".";
				lastdir = 0;
			} else {
				firstbase = 0;
			}
		}

		if (subr == DIF_SUBR_DIRNAME) {
			if (lastdir == -1) {
				/*
				 * We know that we have a slash in the name --
				 * or lastdir would be set to 0, above.  And
				 * because lastdir is -1, we know that this
				 * slash must be the first character.  (That
				 * is, the full string must be of the form
				 * "/basename".)  In this case, the last
				 * character of the directory name is 0.
				 */
				lastdir = 0;
			}

			start = 0;
			end = lastdir;
		} else {
			ASSERT(subr == DIF_SUBR_BASENAME);
			ASSERT(firstbase != -1 && lastbase != -1);
			start = firstbase;
			end = lastbase;
		}

		for (i = start, j = 0; i <= end && (uint64_t)j < size - 1; i++, j++)
			dest[j] = dtrace_load8(src + i);

		dest[j] = '\0';
		regs[rd] = (uintptr_t)dest;
		mstate->dtms_scratch_ptr += size;
		break;
	}

	case DIF_SUBR_CLEANPATH: {
		char *dest = (char *)mstate->dtms_scratch_ptr, c;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uintptr_t src = tupregs[0].dttk_value;
		size_t lim;
		size_t i = 0, j = 0;

		if (!dtrace_strcanload(src, size, &lim, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		/*
		 * Move forward, loading each character.
		 */
		do {
			c = (i >= lim) ? '\0' : dtrace_load8(src + i++);
next:
			if ((uint64_t)(j + 5) >= size)	/* 5 = strlen("/..c\0") */
				break;

			if (c != '/') {
				dest[j++] = c;
				continue;
			}

			c = (i >= lim) ? '\0' : dtrace_load8(src + i++);

			if (c == '/') {
				/*
				 * We have two slashes -- we can just advance
				 * to the next character.
				 */
				goto next;
			}

			if (c != '.') {
				/*
				 * This is not "." and it's not ".." -- we can
				 * just store the "/" and this character and
				 * drive on.
				 */
				dest[j++] = '/';
				dest[j++] = c;
				continue;
			}

			c = (i >= lim) ? '\0' : dtrace_load8(src + i++);

			if (c == '/') {
				/*
				 * This is a "/./" component.  We're not going
				 * to store anything in the destination buffer;
				 * we're just going to go to the next component.
				 */
				goto next;
			}

			if (c != '.') {
				/*
				 * This is not ".." -- we can just store the
				 * "/." and this character and continue
				 * processing.
				 */
				dest[j++] = '/';
				dest[j++] = '.';
				dest[j++] = c;
				continue;
			}

			c = (i >= lim) ? '\0' : dtrace_load8(src + i++);

			if (c != '/' && c != '\0') {
				/*
				 * This is not ".." -- it's "..[mumble]".
				 * We'll store the "/.." and this character
				 * and continue processing.
				 */
				dest[j++] = '/';
				dest[j++] = '.';
				dest[j++] = '.';
				dest[j++] = c;
				continue;
			}

			/*
			 * This is "/../" or "/..\0".  We need to back up
			 * our destination pointer until we find a "/".
			 */
			i--;
			while (j != 0 && dest[--j] != '/')
				continue;

			if (c == '\0')
				dest[++j] = '/';
		} while (c != '\0');

		dest[j] = '\0';
		regs[rd] = (uintptr_t)dest;
		mstate->dtms_scratch_ptr += size;
		break;
	}

	case DIF_SUBR_INET_NTOA:
	case DIF_SUBR_INET_NTOA6:
	case DIF_SUBR_INET_NTOP: {
		size_t size;
		int af, argi, i;
		char *base, *end;

		if (subr == DIF_SUBR_INET_NTOP) {
			af = (int)tupregs[0].dttk_value;
			argi = 1;
		} else {
			af = subr == DIF_SUBR_INET_NTOA ? AF_INET: AF_INET6;
			argi = 0;
		}

		if (af == AF_INET) {
#if !defined(__APPLE__)
			ipaddr_t ip4;
#else
			uint32_t ip4;
#endif /* __APPLE__ */
			uint8_t *ptr8, val;

			/*
			 * Safely load the IPv4 address.
			 */
#if !defined(__APPLE__)			
			ip4 = dtrace_load32(tupregs[argi].dttk_value);
#else
			if (!dtrace_canload(tupregs[argi].dttk_value, sizeof(ip4),
				mstate, vstate)) {
				regs[rd] = 0;
				break;
			}

			dtrace_bcopy(
			    (void *)(uintptr_t)tupregs[argi].dttk_value,
			    (void *)(uintptr_t)&ip4, sizeof (ip4));
#endif /* __APPLE__ */			
			/*
			 * Check an IPv4 string will fit in scratch.
			 */
#if !defined(__APPLE__)
			size = INET_ADDRSTRLEN;
#else
			size = MAX_IPv4_STR_LEN;
#endif /* __APPLE__ */
			if (!DTRACE_INSCRATCH(mstate, size)) {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
				regs[rd] = 0;
				break;
			}
			base = (char *)mstate->dtms_scratch_ptr;
			end = (char *)mstate->dtms_scratch_ptr + size - 1;

			/*
			 * Stringify as a dotted decimal quad.
			 */
			*end-- = '\0';
			ptr8 = (uint8_t *)&ip4;
			for (i = 3; i >= 0; i--) {
				val = ptr8[i];

				if (val == 0) {
					*end-- = '0';
				} else {
					for (; val; val /= 10) {
						*end-- = '0' + (val % 10);
					}
				}

				if (i > 0)
					*end-- = '.';
			}
			ASSERT(end + 1 >= base);

		} else if (af == AF_INET6) {
#if defined(__APPLE__)
#define _S6_un __u6_addr
#define _S6_u8 __u6_addr8
#endif /* __APPLE__ */
			struct in6_addr ip6;
			int firstzero, tryzero, numzero, v6end;
			uint16_t val;
			const char digits[] = "0123456789abcdef";

			/*
			 * Stringify using RFC 1884 convention 2 - 16 bit
			 * hexadecimal values with a zero-run compression.
			 * Lower case hexadecimal digits are used.
			 * 	eg, fe80::214:4fff:fe0b:76c8.
			 * The IPv4 embedded form is returned for inet_ntop,
			 * just the IPv4 string is returned for inet_ntoa6.
			 */

			if (!dtrace_canload(tupregs[argi].dttk_value,
				sizeof(struct in6_addr), mstate, vstate)) {
				regs[rd] = 0;
				break;
			}

			/*
			 * Safely load the IPv6 address.
			 */
			dtrace_bcopy(
			    (void *)(uintptr_t)tupregs[argi].dttk_value,
			    (void *)(uintptr_t)&ip6, sizeof (struct in6_addr));

			/*
			 * Check an IPv6 string will fit in scratch.
			 */
			size = INET6_ADDRSTRLEN;
			if (!DTRACE_INSCRATCH(mstate, size)) {
				DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
				regs[rd] = 0;
				break;
			}
			base = (char *)mstate->dtms_scratch_ptr;
			end = (char *)mstate->dtms_scratch_ptr + size - 1;
			*end-- = '\0';

			/*
			 * Find the longest run of 16 bit zero values
			 * for the single allowed zero compression - "::".
			 */
			firstzero = -1;
			tryzero = -1;
			numzero = 1;
			for (i = 0; i < (int)sizeof (struct in6_addr); i++) {
				if (ip6._S6_un._S6_u8[i] == 0 &&
				    tryzero == -1 && i % 2 == 0) {
					tryzero = i;
					continue;
				}

				if (tryzero != -1 &&
				    (ip6._S6_un._S6_u8[i] != 0 ||
				    i == sizeof (struct in6_addr) - 1)) {

					if (i - tryzero <= numzero) {
						tryzero = -1;
						continue;
					}

					firstzero = tryzero;
					numzero = i - i % 2 - tryzero;
					tryzero = -1;

					if (ip6._S6_un._S6_u8[i] == 0 &&
					    i == sizeof (struct in6_addr) - 1)
						numzero += 2;
				}
			}
			ASSERT(firstzero + numzero <= (int)sizeof (struct in6_addr));

			/*
			 * Check for an IPv4 embedded address.
			 */
			v6end = sizeof (struct in6_addr) - 2;
			if (IN6_IS_ADDR_V4MAPPED(&ip6) ||
			    IN6_IS_ADDR_V4COMPAT(&ip6)) {
				for (i = sizeof (struct in6_addr) - 1;
				     i >= (int)DTRACE_V4MAPPED_OFFSET; i--) {
					ASSERT(end >= base);

					val = ip6._S6_un._S6_u8[i];

					if (val == 0) {
						*end-- = '0';
					} else {
						for (; val; val /= 10) {
							*end-- = '0' + val % 10;
						}
					}

					if (i > (int)DTRACE_V4MAPPED_OFFSET)
						*end-- = '.';
				}

				if (subr == DIF_SUBR_INET_NTOA6)
					goto inetout;

				/*
				 * Set v6end to skip the IPv4 address that
				 * we have already stringified.
				 */
				v6end = 10;
			}

			/*
			 * Build the IPv6 string by working through the
			 * address in reverse.
			 */
			for (i = v6end; i >= 0; i -= 2) {
				ASSERT(end >= base);

				if (i == firstzero + numzero - 2) {
					*end-- = ':';
					*end-- = ':';
					i -= numzero - 2;
					continue;
				}

				if (i < 14 && i != firstzero - 2)
					*end-- = ':';

				val = (ip6._S6_un._S6_u8[i] << 8) +
				    ip6._S6_un._S6_u8[i + 1];

				if (val == 0) {
					*end-- = '0';
				} else {
					for (; val; val /= 16) {
						*end-- = digits[val % 16];
					}
				}
			}
			ASSERT(end + 1 >= base);

#if defined(__APPLE__)
#undef _S6_un
#undef _S6_u8
#endif /* __APPLE__ */
		} else {
			/*
			 * The user didn't use AH_INET or AH_INET6.
			 */
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			regs[rd] = 0;
			break;
		}

inetout:	regs[rd] = (uintptr_t)end + 1;
		mstate->dtms_scratch_ptr += size;
		break;
	}

	case DIF_SUBR_TOUPPER:
	case DIF_SUBR_TOLOWER: {
		uintptr_t src = tupregs[0].dttk_value;
		char *dest = (char *)mstate->dtms_scratch_ptr;
		char lower, upper, base, c;
		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		size_t len = dtrace_strlen((char*) src, size);
		size_t i = 0;

		lower = (subr == DIF_SUBR_TOUPPER) ? 'a' : 'A';
		upper = (subr == DIF_SUBR_TOUPPER) ? 'z' : 'Z';
		base  = (subr == DIF_SUBR_TOUPPER) ? 'A' : 'a';

		if (!dtrace_canload(src, len + 1, mstate, vstate)) {
			regs[rd] = 0;
			break;
		}

		if (!DTRACE_INSCRATCH(mstate, size)) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_NOSCRATCH);
			regs[rd] = 0;
			break;
		}

		for (i = 0; i < size - 1; ++i) {
			if ((c = dtrace_load8(src + i)) == '\0')
				break;
			if (c >= lower && c <= upper)
				c = base + (c - lower);
			dest[i] = c;
		}

		ASSERT(i < size);

		dest[i] = '\0';
		regs[rd] = (uintptr_t) dest;
		mstate->dtms_scratch_ptr += size;

		break;
	}

#if defined(__APPLE__)
	case DIF_SUBR_VM_KERNEL_ADDRPERM: {
		if (!dtrace_priv_kernel(state)) {
			regs[rd] = 0;
		} else {
			regs[rd] = VM_KERNEL_ADDRPERM((vm_offset_t) tupregs[0].dttk_value);
		}

		break;
	}

	case DIF_SUBR_KDEBUG_TRACE: {
		uint32_t debugid;
		uintptr_t args[4] = {0};
		int i;

		if (nargs < 2 || nargs > 5) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			break;
		}

		if (dtrace_destructive_disallow)
			return;

		debugid = tupregs[0].dttk_value;
		for (i = 0; i < nargs - 1; i++)
			args[i] = tupregs[i + 1].dttk_value;

		kernel_debug(debugid, args[0], args[1], args[2], args[3], 0);

		break;
	}

	case DIF_SUBR_KDEBUG_TRACE_STRING: {
		if (nargs != 3) {
			break;
		}

		if (dtrace_destructive_disallow)
			return;

		uint64_t size = state->dts_options[DTRACEOPT_STRSIZE];
		uint32_t debugid = tupregs[0].dttk_value;
		uint64_t str_id = tupregs[1].dttk_value;
		uintptr_t src = tupregs[2].dttk_value;
		size_t lim;
		char buf[size];
		char* str = NULL;

		if (src != (uintptr_t)0) {
			str = buf;
			if (!dtrace_strcanload(src, size, &lim, mstate, vstate)) {
				break;
			}
			dtrace_strcpy((void*)src, buf, size);
		}

		(void)kernel_debug_string(debugid, &str_id, str);
		regs[rd] = str_id;

		break;
	}
#endif

	}
}