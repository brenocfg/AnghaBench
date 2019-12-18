#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  service; void* major; void* minor; } ;
typedef  TYPE_1__ tBTA_UTL_COD ;
typedef  void* UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_COD_MAJOR_CLASS (void*,void**) ; 
 int /*<<< orphan*/  BTM_COD_MINOR_CLASS (void*,void**) ; 
 int /*<<< orphan*/  BTM_COD_SERVICE_CLASS (int /*<<< orphan*/ ,void**) ; 
 void** BTM_ReadDeviceClass () ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN utl_get_device_class(tBTA_UTL_COD *p_cod)
{
    UINT8 *dev;
    UINT16 service;
    UINT8  minor, major;

    dev = BTM_ReadDeviceClass();
    BTM_COD_SERVICE_CLASS( service, dev );
    BTM_COD_MINOR_CLASS(minor, dev );
    BTM_COD_MAJOR_CLASS(major, dev );

    p_cod->minor = minor;
    p_cod->major = major;
    p_cod->service = service;

    return TRUE;
}