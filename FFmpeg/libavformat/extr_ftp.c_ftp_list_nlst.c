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
 int /*<<< orphan*/  NLST ; 
 int ftp_send_command (TYPE_1__*,char const*,int const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_list_nlst(FTPContext *s)
{
    static const char *command = "NLST\r\n";
    static const int nlst_codes[] = {226, 425, 426, 451, 450, 550, 0};

    if (ftp_send_command(s, command, nlst_codes, NULL) != 226)
        return AVERROR(ENOSYS);
    s->listing_method = NLST;
    return 0;
}