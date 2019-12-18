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
struct xdr_stream {int dummy; } ;
struct nsm_args {int /*<<< orphan*/  mon_name; } ;

/* Variables and functions */
 int encode_nsm_string (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encode_mon_name(struct xdr_stream *xdr, const struct nsm_args *argp)
{
	return encode_nsm_string(xdr, argp->mon_name);
}