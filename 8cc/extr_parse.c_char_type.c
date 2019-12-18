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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
#define  ENC_CHAR16 131 
#define  ENC_CHAR32 130 
#define  ENC_NONE 129 
#define  ENC_WCHAR 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * type_int ; 
 int /*<<< orphan*/ * type_uint ; 
 int /*<<< orphan*/ * type_ushort ; 

__attribute__((used)) static Type *char_type(int enc) {
    switch (enc) {
    case ENC_NONE:
    case ENC_WCHAR:
        return type_int;
    case ENC_CHAR16:
        return type_ushort;
    case ENC_CHAR32:
        return type_uint;
    }
    error("internal error");
}