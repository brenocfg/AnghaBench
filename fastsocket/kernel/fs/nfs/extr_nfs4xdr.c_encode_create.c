#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct TYPE_6__ {int specdata1; int specdata2; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  pages; } ;
struct TYPE_7__ {TYPE_2__ device; TYPE_1__ symlink; } ;
struct nfs4_create_arg {int ftype; int /*<<< orphan*/  server; int /*<<< orphan*/  attrs; TYPE_4__* name; TYPE_3__ u; } ;
struct compound_hdr {int /*<<< orphan*/  replen; int /*<<< orphan*/  nops; } ;
typedef  void* __be32 ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;

/* Variables and functions */
#define  NF4BLK 130 
#define  NF4CHR 129 
#define  NF4LNK 128 
 int OP_CREATE ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ decode_create_maxsz ; 
 int /*<<< orphan*/  encode_attrs (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_string (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_write_pages (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encode_create(struct xdr_stream *xdr, const struct nfs4_create_arg *create, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 8);
	*p++ = cpu_to_be32(OP_CREATE);
	*p = cpu_to_be32(create->ftype);

	switch (create->ftype) {
	case NF4LNK:
		p = reserve_space(xdr, 4);
		*p = cpu_to_be32(create->u.symlink.len);
		xdr_write_pages(xdr, create->u.symlink.pages, 0, create->u.symlink.len);
		break;

	case NF4BLK: case NF4CHR:
		p = reserve_space(xdr, 8);
		*p++ = cpu_to_be32(create->u.device.specdata1);
		*p = cpu_to_be32(create->u.device.specdata2);
		break;

	default:
		break;
	}

	encode_string(xdr, create->name->len, create->name->name);
	hdr->nops++;
	hdr->replen += decode_create_maxsz;

	encode_attrs(xdr, create->attrs, create->server);
}