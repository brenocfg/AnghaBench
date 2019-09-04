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
struct ccdrbg_nisthmac_state {int dummy; } ;
struct ccdrbg_nisthmac_custom {int dummy; } ;
struct ccdrbg_info {int size; struct ccdrbg_nisthmac_custom const* custom; int /*<<< orphan*/  done; int /*<<< orphan*/  reseed; int /*<<< orphan*/  generate; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  generate ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  reseed ; 

void ccdrbg_factory_nisthmac(struct ccdrbg_info *info, const struct ccdrbg_nisthmac_custom *custom)
{
    info->size = sizeof(struct ccdrbg_nisthmac_state) + sizeof(struct ccdrbg_nisthmac_custom);
    info->init = init;
    info->generate = generate;
    info->reseed = reseed;
    info->done = done;
    info->custom = custom;
}