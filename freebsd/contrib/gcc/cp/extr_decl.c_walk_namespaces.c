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
typedef  int /*<<< orphan*/  walk_namespaces_fn ;

/* Variables and functions */
 int /*<<< orphan*/  global_namespace ; 
 int walk_namespaces_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
walk_namespaces (walk_namespaces_fn f, void* data)
{
  return walk_namespaces_r (global_namespace, f, data);
}