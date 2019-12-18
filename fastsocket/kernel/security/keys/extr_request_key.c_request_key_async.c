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
struct key_type {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALLOC_IN_QUOTA ; 
 struct key* request_key_and_link (struct key_type*,char const*,void const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct key *request_key_async(struct key_type *type,
			      const char *description,
			      const void *callout_info,
			      size_t callout_len)
{
	return request_key_and_link(type, description, callout_info,
				    callout_len, NULL, NULL,
				    KEY_ALLOC_IN_QUOTA);
}