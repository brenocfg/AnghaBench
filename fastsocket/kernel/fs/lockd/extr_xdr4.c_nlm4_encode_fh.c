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
struct nfs_fh {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int XDR_QUADLEN (scalar_t__) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __be32 *
nlm4_encode_fh(__be32 *p, struct nfs_fh *f)
{
	*p++ = htonl(f->size);
	if (f->size) p[XDR_QUADLEN(f->size)-1] = 0; /* don't leak anything */
	memcpy(p, f->data, f->size);
	return p + XDR_QUADLEN(f->size);
}