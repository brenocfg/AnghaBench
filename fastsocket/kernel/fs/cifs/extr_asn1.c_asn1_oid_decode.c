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
struct asn1_ctx {unsigned char* pointer; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ERR_DEC_BADVALUE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  asn1_subid_decode (struct asn1_ctx*,unsigned long*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
asn1_oid_decode(struct asn1_ctx *ctx,
		unsigned char *eoc, unsigned long **oid, unsigned int *len)
{
	unsigned long subid;
	unsigned int size;
	unsigned long *optr;

	size = eoc - ctx->pointer + 1;

	/* first subid actually encodes first two subids */
	if (size < 2 || size > UINT_MAX/sizeof(unsigned long))
		return 0;

	*oid = kmalloc(size * sizeof(unsigned long), GFP_ATOMIC);
	if (*oid == NULL)
		return 0;

	optr = *oid;

	if (!asn1_subid_decode(ctx, &subid)) {
		kfree(*oid);
		*oid = NULL;
		return 0;
	}

	if (subid < 40) {
		optr[0] = 0;
		optr[1] = subid;
	} else if (subid < 80) {
		optr[0] = 1;
		optr[1] = subid - 40;
	} else {
		optr[0] = 2;
		optr[1] = subid - 80;
	}

	*len = 2;
	optr += 2;

	while (ctx->pointer < eoc) {
		if (++(*len) > size) {
			ctx->error = ASN1_ERR_DEC_BADVALUE;
			kfree(*oid);
			*oid = NULL;
			return 0;
		}

		if (!asn1_subid_decode(ctx, optr++)) {
			kfree(*oid);
			*oid = NULL;
			return 0;
		}
	}
	return 1;
}