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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t wcwidth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
mbswidth(const char *month)
{
	wchar_t wc;
	size_t width, donelen, clen, w;

	width = donelen = 0;
	while ((clen = mbrtowc(&wc, month + donelen, MB_LEN_MAX, NULL)) != 0) {
		if (clen == (size_t)-1 || clen == (size_t)-2)
			return (-1);
		donelen += clen;
		if ((w = wcwidth(wc)) == (size_t)-1)
			return (-1);
		width += w;
	}

	return (width);
}