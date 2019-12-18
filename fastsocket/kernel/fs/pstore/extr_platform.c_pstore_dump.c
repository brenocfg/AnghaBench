#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kmsg_dumper {int dummy; } ;
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;
struct TYPE_3__ {char* buf; int bufsize; int (* write ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,int,int,TYPE_1__*) ;int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int KMSG_DUMP_OOPS ; 
 int /*<<< orphan*/  PSTORE_TYPE_DMESG ; 
 char* get_reason_str (int) ; 
 scalar_t__ in_nmi () ; 
 unsigned long kmsg_bytes ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int oopscount ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__* psinfo ; 
 scalar_t__ pstore_is_mounted () ; 
 int pstore_new_entry ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sprintf (char*,char*,char const*,int,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,int,int,TYPE_1__*) ; 

__attribute__((used)) static void pstore_dump(struct kmsg_dumper *dumper,
	    enum kmsg_dump_reason reason,
	    const char *s1, unsigned long l1,
	    const char *s2, unsigned long l2)
{
	unsigned long	s1_start, s2_start;
	unsigned long	l1_cpy, l2_cpy;
	unsigned long	size, total = 0;
	char		*dst;
	const char	*why;
	u64		id;
	int		hsize, ret;
	unsigned int	part = 1;
	unsigned long	flags = 0;
	int		is_locked = 0;

	why = get_reason_str(reason);

	if (in_nmi()) {
		is_locked = spin_trylock(&psinfo->buf_lock);
		if (!is_locked)
			pr_err("pstore dump routine blocked in NMI, may corrupt error record\n");
	} else
		spin_lock_irqsave(&psinfo->buf_lock, flags);
	oopscount++;
	while (total < kmsg_bytes) {
		dst = psinfo->buf;
		hsize = sprintf(dst, "%s#%d Part%d\n", why, oopscount, part);
		size = psinfo->bufsize - hsize;
		dst += hsize;

		l2_cpy = min(l2, size);
		l1_cpy = min(l1, size - l2_cpy);

		if (l1_cpy + l2_cpy == 0)
			break;

		s2_start = l2 - l2_cpy;
		s1_start = l1 - l1_cpy;

		memcpy(dst, s1 + s1_start, l1_cpy);
		memcpy(dst + l1_cpy, s2 + s2_start, l2_cpy);

		ret = psinfo->write(PSTORE_TYPE_DMESG, reason, &id, part,
				    oopscount, hsize + l1_cpy + l2_cpy, psinfo);
		if (ret == 0 && reason == KMSG_DUMP_OOPS && pstore_is_mounted())
			pstore_new_entry = 1;
		l1 -= l1_cpy;
		l2 -= l2_cpy;
		total += l1_cpy + l2_cpy;
		part++;
	}
	if (in_nmi()) {
		if (is_locked)
			spin_unlock(&psinfo->buf_lock);
	} else
		spin_unlock_irqrestore(&psinfo->buf_lock, flags);
}