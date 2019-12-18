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

/* Variables and functions */
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_static2 () ; 
 int /*<<< orphan*/  local_static3 () ; 

__attribute__((used)) static void local_static() {
    expect(6, local_static2());
    expect(7, local_static2());
    local_static3();
    expect(8, local_static2());
}