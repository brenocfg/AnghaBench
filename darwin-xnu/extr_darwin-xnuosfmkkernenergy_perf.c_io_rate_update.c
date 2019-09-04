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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  io_rate_update_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t io_rate_update(uint64_t io_rate_flags, uint64_t read_ops_delta, uint64_t write_ops_delta, uint64_t read_bytes_delta, uint64_t write_bytes_delta) {
	return io_rate_update_cb(io_rate_flags, read_ops_delta, write_ops_delta, read_bytes_delta, write_bytes_delta);
}