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
typedef  char u8 ;
typedef  int u16 ;
struct super_block {int dummy; } ;
struct nls_table {int (* uni2char ) (int,char*,int) ;} ;
struct hfsplus_unistr {int /*<<< orphan*/  const length; int /*<<< orphan*/ * unicode; } ;
typedef  int /*<<< orphan*/  hfsplus_unichr ;
struct TYPE_2__ {int flags; struct nls_table* nls; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 TYPE_1__ HFSPLUS_SB (struct super_block*) ; 
 int HFSPLUS_SB_NODECOMPOSE ; 
 int Hangul_LBase ; 
 scalar_t__ Hangul_SBase ; 
 int Hangul_TBase ; 
 int Hangul_TCount ; 
 int Hangul_VBase ; 
 int Hangul_VCount ; 
 int be16_to_cpu (int /*<<< orphan*/  const) ; 
 int* hfsplus_compose_lookup (int*,int) ; 
 int* hfsplus_compose_table ; 
 scalar_t__ likely (int) ; 
 int stub1 (int,char*,int) ; 
 int stub2 (int,char*,int) ; 

int hfsplus_uni2asc(struct super_block *sb, const struct hfsplus_unistr *ustr, char *astr, int *len_p)
{
	const hfsplus_unichr *ip;
	struct nls_table *nls = HFSPLUS_SB(sb).nls;
	u8 *op;
	u16 cc, c0, c1;
	u16 *ce1, *ce2;
	int i, len, ustrlen, res, compose;

	op = astr;
	ip = ustr->unicode;
	ustrlen = be16_to_cpu(ustr->length);
	len = *len_p;
	ce1 = NULL;
	compose = !(HFSPLUS_SB(sb).flags & HFSPLUS_SB_NODECOMPOSE);

	while (ustrlen > 0) {
		c0 = be16_to_cpu(*ip++);
		ustrlen--;
		/* search for single decomposed char */
		if (likely(compose))
			ce1 = hfsplus_compose_lookup(hfsplus_compose_table, c0);
		if (ce1 && (cc = ce1[0])) {
			/* start of a possibly decomposed Hangul char */
			if (cc != 0xffff)
				goto done;
			if (!ustrlen)
				goto same;
			c1 = be16_to_cpu(*ip) - Hangul_VBase;
			if (c1 < Hangul_VCount) {
				/* compose the Hangul char */
				cc = (c0 - Hangul_LBase) * Hangul_VCount;
				cc = (cc + c1) * Hangul_TCount;
				cc += Hangul_SBase;
				ip++;
				ustrlen--;
				if (!ustrlen)
					goto done;
				c1 = be16_to_cpu(*ip) - Hangul_TBase;
				if (c1 > 0 && c1 < Hangul_TCount) {
					cc += c1;
					ip++;
					ustrlen--;
				}
				goto done;
			}
		}
		while (1) {
			/* main loop for common case of not composed chars */
			if (!ustrlen)
				goto same;
			c1 = be16_to_cpu(*ip);
			if (likely(compose))
				ce1 = hfsplus_compose_lookup(hfsplus_compose_table, c1);
			if (ce1)
				break;
			switch (c0) {
			case 0:
				c0 = 0x2400;
				break;
			case '/':
				c0 = ':';
				break;
			}
			res = nls->uni2char(c0, op, len);
			if (res < 0) {
				if (res == -ENAMETOOLONG)
					goto out;
				*op = '?';
				res = 1;
			}
			op += res;
			len -= res;
			c0 = c1;
			ip++;
			ustrlen--;
		}
		ce2 = hfsplus_compose_lookup(ce1, c0);
		if (ce2) {
			i = 1;
			while (i < ustrlen) {
				ce1 = hfsplus_compose_lookup(ce2, be16_to_cpu(ip[i]));
				if (!ce1)
					break;
				i++;
				ce2 = ce1;
			}
			if ((cc = ce2[0])) {
				ip += i;
				ustrlen -= i;
				goto done;
			}
		}
	same:
		switch (c0) {
		case 0:
			cc = 0x2400;
			break;
		case '/':
			cc = ':';
			break;
		default:
			cc = c0;
		}
	done:
		res = nls->uni2char(cc, op, len);
		if (res < 0) {
			if (res == -ENAMETOOLONG)
				goto out;
			*op = '?';
			res = 1;
		}
		op += res;
		len -= res;
	}
	res = 0;
out:
	*len_p = (char *)op - astr;
	return res;
}