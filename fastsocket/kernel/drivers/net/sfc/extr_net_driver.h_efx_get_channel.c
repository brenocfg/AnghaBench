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
struct efx_nic {unsigned int n_channels; struct efx_channel** channel; } ;
struct efx_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 

__attribute__((used)) static inline struct efx_channel *
efx_get_channel(struct efx_nic *efx, unsigned index)
{
	EFX_BUG_ON_PARANOID(index >= efx->n_channels);
	return efx->channel[index];
}