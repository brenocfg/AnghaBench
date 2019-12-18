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
typedef  scalar_t__ wchar_t ;
typedef  char ucs2_t ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mbstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int mbrtowc (scalar_t__*,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static size_t _FAT_directory_mbstoucs2 (ucs2_t* dst, const char* src, size_t len) {
	mbstate_t ps = {0};
	wchar_t tempChar;
	int bytes;
	size_t count = 0;

	while (count < len-1 && *src != '\0') {
		bytes = mbrtowc (&tempChar, src, MB_CUR_MAX, &ps);
		if (bytes > 0) {
			*dst = (ucs2_t)tempChar;
			src += bytes;
			dst++;
			count++;
		} else if (bytes == 0) {
			break;
		} else {
			return -1;
		}
	}
	*dst = '\0';

	return count;
}