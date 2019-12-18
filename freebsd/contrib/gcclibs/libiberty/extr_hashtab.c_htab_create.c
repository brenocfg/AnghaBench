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
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  htab_hash ;
typedef  int /*<<< orphan*/  htab_eq ;
typedef  int /*<<< orphan*/  htab_del ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  htab_create_alloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcalloc ; 

htab_t
htab_create (size_t size, htab_hash hash_f, htab_eq eq_f, htab_del del_f)
{
  return htab_create_alloc (size, hash_f, eq_f, del_f, xcalloc, free);
}