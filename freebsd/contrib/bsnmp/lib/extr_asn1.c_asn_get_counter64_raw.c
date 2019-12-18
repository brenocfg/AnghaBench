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
typedef  int /*<<< orphan*/  uint64_t ;
struct asn_buf {int dummy; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int /*<<< orphan*/  asn_len_t ;

/* Variables and functions */
 int asn_get_real_unsigned (struct asn_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

enum asn_err
asn_get_counter64_raw(struct asn_buf *b, asn_len_t len, uint64_t *vp)
{
	return (asn_get_real_unsigned(b, len, vp));
}