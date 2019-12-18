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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  construct_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

var new_raw_with(var type, var args) { 
  return construct_with(alloc_raw(type), args);
}