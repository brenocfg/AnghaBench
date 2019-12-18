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
typedef  int /*<<< orphan*/  mbuf_tag_id_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSI_MBUF_TAG ; 
 int /*<<< orphan*/  net_str_id_find_internal (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

errno_t
mbuf_tag_id_find(
	const char		*string,
	mbuf_tag_id_t	*out_id)
{
	return (net_str_id_find_internal(string, out_id, NSI_MBUF_TAG, 1));
}