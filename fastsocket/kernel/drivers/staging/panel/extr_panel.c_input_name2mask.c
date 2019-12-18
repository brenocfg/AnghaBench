#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sigtab ;
typedef  unsigned long long pmask_t ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static int input_name2mask(char *name, pmask_t *mask, pmask_t *value,
			   char *imask, char *omask)
{
	static char sigtab[10] = "EeSsPpAaBb";
	char im, om;
	pmask_t m, v;

	om = im = m = v = 0ULL;
	while (*name) {
		int in, out, bit, neg;
		for (in = 0; (in < sizeof(sigtab)) && (sigtab[in] != *name); in++)
			;
		if (in >= sizeof(sigtab))
			return 0;	/* input name not found */
		neg = (in & 1);	/* odd (lower) names are negated */
		in >>= 1;
		im |= (1 << in);

		name++;
		if (isdigit(*name)) {
			out = *name - '0';
			om |= (1 << out);
		} else if (*name == '-')
			out = 8;
		else
			return 0;	/* unknown bit name */

		bit = (out * 5) + in;

		m |= 1ULL << bit;
		if (!neg)
			v |= 1ULL << bit;
		name++;
	}
	*mask = m;
	*value = v;
	if (imask)
		*imask |= im;
	if (omask)
		*omask |= om;
	return 1;
}