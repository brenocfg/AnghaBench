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

/* Variables and functions */
#define  ENC_CHAR16 131 
#define  ENC_CHAR32 130 
#define  ENC_UTF8 129 
#define  ENC_WCHAR 128 

__attribute__((used)) static char *encoding_prefix(int enc) {
    switch (enc) {
    case ENC_CHAR16: return "u";
    case ENC_CHAR32: return "U";
    case ENC_UTF8:   return "u8";
    case ENC_WCHAR:  return "L";
    }
    return "";
}