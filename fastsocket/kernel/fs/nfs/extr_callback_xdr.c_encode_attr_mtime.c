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
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int const FATTR4_WORD1_TIME_MODIFY ; 
 int /*<<< orphan*/  encode_attr_time (struct xdr_stream*,struct timespec const*) ; 

__attribute__((used)) static __be32 encode_attr_mtime(struct xdr_stream *xdr, const uint32_t *bitmap, const struct timespec *time)
{
	if (!(bitmap[1] & FATTR4_WORD1_TIME_MODIFY))
		return 0;
	return encode_attr_time(xdr,time);
}