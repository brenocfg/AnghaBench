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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_link_hci_qos_violation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_qos_violation_evt (UINT8 *p)
{
    UINT16   handle;

    STREAM_TO_UINT16 (handle, p);

    handle = HCID_GET_HANDLE (handle);


    l2c_link_hci_qos_violation (handle);
}