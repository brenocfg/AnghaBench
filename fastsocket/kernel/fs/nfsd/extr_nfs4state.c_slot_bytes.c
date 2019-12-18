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
struct nfsd4_channel_attrs {int maxresp_cached; } ;

/* Variables and functions */
 int NFSD_MIN_HDR_SEQ_SZ ; 

__attribute__((used)) static inline int slot_bytes(struct nfsd4_channel_attrs *ca)
{
	return ca->maxresp_cached - NFSD_MIN_HDR_SEQ_SZ;
}