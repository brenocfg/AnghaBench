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
typedef  int /*<<< orphan*/  LSTATUS ;
typedef  scalar_t__* LPCWSTR ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 int /*<<< orphan*/  RegCreateKeyExW (scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegSetValueExW (scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LSTATUS regset(HKEY hkey,
      LPCWSTR subkey,
      LPCWSTR name,
      DWORD type,
      const void* data,
      DWORD len)
{
    HKEY htkey = hkey, hsubkey = NULL;
    LSTATUS ret;
    if (subkey && subkey[0])
    {
        if ((ret = RegCreateKeyExW(hkey, subkey, 0, 0, 0, KEY_ALL_ACCESS, 0, &hsubkey, 0)) !=
            ERROR_SUCCESS)
            return ret;
        htkey = hsubkey;
    }
    ret = RegSetValueExW(htkey, name, 0, type, (const BYTE*)data, len);
    if (hsubkey && hsubkey != hkey)
        RegCloseKey(hsubkey);
    return ret;
}