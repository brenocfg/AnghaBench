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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
typedef  int /*<<< orphan*/  PLCI ;
typedef  int /*<<< orphan*/  DIVA_CAPI_ADAPTER ;
typedef  int /*<<< orphan*/  APPL ;
typedef  int /*<<< orphan*/  API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 

__attribute__((used)) static byte facility_res(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
			 PLCI *plci, APPL *appl, API_PARSE *msg)
{
  dbug(1,dprintf("facility_res"));
  return false;
}