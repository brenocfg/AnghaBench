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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_line(AVIOContext * pb, char* line, int bufsize)
{
    int i;
    for (i = 0; i < bufsize - 1; i++) {
        int b = avio_r8(pb);
        if (b == 0)
            break;
        if (b == '\n') {
            line[i] = '\0';
            return avio_feof(pb) ? -1 : 0;
        }
        line[i] = b;
    }
    line[i] = '\0';
    return -1;
}