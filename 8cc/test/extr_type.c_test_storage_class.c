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
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  c ; 

__attribute__((used)) static void test_storage_class() {
    static a;
    auto b;
    register c;
    static int d;
    auto int e;
    register int f;
}