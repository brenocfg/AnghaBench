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
typedef  int uint8_t ;
typedef  unsigned int uint16_t ;
struct ustr {unsigned int u_len; int /*<<< orphan*/ * u_name; } ;
struct nls_table {int (* char2uni ) (int /*<<< orphan*/ *,unsigned int,unsigned int*) ;} ;
typedef  int dstring ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 

__attribute__((used)) static int udf_NLStoCS0(struct nls_table *nls, dstring *ocu, struct ustr *uni,
			int length)
{
	int len;
	unsigned i, max_val;
	uint16_t uni_char;
	int u_len;

	memset(ocu, 0, sizeof(dstring) * length);
	ocu[0] = 8;
	max_val = 0xffU;

try_again:
	u_len = 0U;
	for (i = 0U; i < uni->u_len; i++) {
		len = nls->char2uni(&uni->u_name[i], uni->u_len - i, &uni_char);
		if (!len)
			continue;
		/* Invalid character, deal with it */
		if (len < 0) {
			len = 1;
			uni_char = '?';
		}

		if (uni_char > max_val) {
			max_val = 0xffffU;
			ocu[0] = (uint8_t)0x10U;
			goto try_again;
		}

		if (max_val == 0xffffU)
			ocu[++u_len] = (uint8_t)(uni_char >> 8);
		ocu[++u_len] = (uint8_t)(uni_char & 0xffU);
		i += len - 1;
	}

	ocu[length - 1] = (uint8_t)u_len + 1;
	return u_len + 1;
}