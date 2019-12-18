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
struct entropy_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mix_pool_bytes_extract (struct entropy_store*,void const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mix_pool_bytes(struct entropy_store *r, const void *in, int bytes)
{
       mix_pool_bytes_extract(r, in, bytes, NULL);
}