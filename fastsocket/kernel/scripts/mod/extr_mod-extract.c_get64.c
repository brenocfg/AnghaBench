#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get64 ) (int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 TYPE_1__* order ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline uint64_t get64(const uint64_t *p) { return order->get64(p); }