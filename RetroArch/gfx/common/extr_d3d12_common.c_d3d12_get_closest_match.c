#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  format_support ;
struct TYPE_4__ {scalar_t__ Format; scalar_t__ member_0; int Support1; int Support2; } ;
typedef  scalar_t__ DXGI_FORMAT ;
typedef  TYPE_1__ D3D12_FEATURE_DATA_FORMAT_SUPPORT ;
typedef  int /*<<< orphan*/  D3D12Device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12CheckFeatureSupport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  D3D12_FEATURE_FORMAT_SUPPORT ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 scalar_t__* dxgi_get_format_fallback_list (scalar_t__) ; 

DXGI_FORMAT d3d12_get_closest_match(D3D12Device device, D3D12_FEATURE_DATA_FORMAT_SUPPORT* desired)
{
   DXGI_FORMAT  default_list[] = { desired->Format, DXGI_FORMAT_UNKNOWN };
   DXGI_FORMAT* format         = dxgi_get_format_fallback_list(desired->Format);

   if (!format)
      format = default_list;

   while (*format != DXGI_FORMAT_UNKNOWN)
   {
      D3D12_FEATURE_DATA_FORMAT_SUPPORT format_support = { *format };
      if (SUCCEEDED(D3D12CheckFeatureSupport(
                device, D3D12_FEATURE_FORMAT_SUPPORT, &format_support, sizeof(format_support))) &&
          ((format_support.Support1 & desired->Support1) == desired->Support1) &&
          ((format_support.Support2 & desired->Support2) == desired->Support2))
         break;
      format++;
   }
   assert(*format);
   return *format;
}