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
struct ccdrbg_state {int dummy; } ;
struct ccdrbg_nisthmac_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc_clear (int,struct ccdrbg_nisthmac_state*) ; 

__attribute__((used)) static void done(struct ccdrbg_state *drbg)
{
    struct ccdrbg_nisthmac_state *state=(struct ccdrbg_nisthmac_state *)drbg;
    cc_clear(sizeof(struct ccdrbg_nisthmac_state), state); //clear v, key as well as internal variables
}