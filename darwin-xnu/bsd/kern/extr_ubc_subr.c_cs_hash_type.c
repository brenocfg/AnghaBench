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
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_hash {int /*<<< orphan*/  cs_type; } ;

/* Variables and functions */

uint8_t cs_hash_type(
    struct cs_hash const * const cs_hash)
{
    return cs_hash->cs_type;
}