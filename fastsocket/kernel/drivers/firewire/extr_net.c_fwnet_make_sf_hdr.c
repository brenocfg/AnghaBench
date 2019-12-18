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
struct rfc2734_header {int w0; int /*<<< orphan*/  w1; } ;

/* Variables and functions */
 int fwnet_set_hdr_dg_size (unsigned int) ; 
 int /*<<< orphan*/  fwnet_set_hdr_dgl (unsigned int) ; 
 int fwnet_set_hdr_fg_off (unsigned int) ; 
 int fwnet_set_hdr_lf (unsigned int) ; 

__attribute__((used)) static inline void fwnet_make_sf_hdr(struct rfc2734_header *hdr,
		unsigned lf, unsigned dg_size, unsigned fg_off, unsigned dgl)
{
	hdr->w0 = fwnet_set_hdr_lf(lf)
		  | fwnet_set_hdr_dg_size(dg_size)
		  | fwnet_set_hdr_fg_off(fg_off);
	hdr->w1 = fwnet_set_hdr_dgl(dgl);
}