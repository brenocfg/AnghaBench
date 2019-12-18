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
 int /*<<< orphan*/  ValueError ; 
 int /*<<< orphan*/  throw (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static var Type_Copy(var self) {
  return throw(ValueError, "Type objects cannot be copied.");
}