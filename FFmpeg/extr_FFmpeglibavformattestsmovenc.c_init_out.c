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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  av_md5_init (int /*<<< orphan*/ ) ; 
 char* cur_name ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 char* format ; 
 int /*<<< orphan*/  md5 ; 
 int /*<<< orphan*/  out ; 
 scalar_t__ out_size ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ write_file ; 

__attribute__((used)) static void init_out(const char *name)
{
    char buf[100];
    cur_name = name;
    snprintf(buf, sizeof(buf), "%s.%s", cur_name, format);

    av_md5_init(md5);
    if (write_file) {
        out = fopen(buf, "wb");
        if (!out)
            perror(buf);
    }
    out_size = 0;
}