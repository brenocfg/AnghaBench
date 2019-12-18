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
typedef  size_t word ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {size_t u_law; } ;
typedef  TYPE_1__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/ ** cip_bc ; 
 int /*<<< orphan*/ * cip_hlc ; 
 int /*<<< orphan*/  ie_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static word find_cip(DIVA_CAPI_ADAPTER *a, byte *bc, byte *hlc)
{
  word i;
  word j;

  for(i=9;i && !ie_compare(bc,cip_bc[i][a->u_law]);i--);

  for(j=16;j<29 &&
           (!ie_compare(bc,cip_bc[j][a->u_law]) || !ie_compare(hlc,cip_hlc[j])); j++);
  if(j==29) return i;
  return j;
}