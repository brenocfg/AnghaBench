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
struct nls_table {int (* uni2char ) (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  NLS_MAX_CHARSET_SIZE ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uni16_to_x8(unsigned char *ascii, __be16 *uni, int len, struct nls_table *nls)
{
	__be16 *ip, ch;
	unsigned char *op;

	ip = uni;
	op = ascii;

	while ((ch = get_unaligned(ip)) && len) {
		int llen;
		llen = nls->uni2char(be16_to_cpu(ch), op, NLS_MAX_CHARSET_SIZE);
		if (llen > 0)
			op += llen;
		else
			*op++ = '?';
		ip++;

		len--;
	}
	*op = 0;
	return (op - ascii);
}