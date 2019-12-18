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
struct TYPE_4__ {int /*<<< orphan*/  listing_method; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MLSD ; 
 int ftp_send_command (TYPE_1__*,char const*,int const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_list_mlsd(FTPContext *s)
{
    static const char *command = "MLSD\r\n";
    static const int mlsd_codes[] = {150, 500, 0}; /* 500 is incorrect code */

    if (ftp_send_command(s, command, mlsd_codes, NULL) != 150)
        return AVERROR(ENOSYS);
    s->listing_method = MLSD;
    return 0;
}