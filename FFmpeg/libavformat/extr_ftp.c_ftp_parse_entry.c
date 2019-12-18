#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int listing_method; } ;
typedef  TYPE_2__ FTPContext ;
typedef  int /*<<< orphan*/  AVIODirEntry ;

/* Variables and functions */
#define  MLSD 130 
#define  NLST 129 
#define  UNKNOWN_METHOD 128 
 int ftp_parse_entry_mlsd (char*,int /*<<< orphan*/ *) ; 
 int ftp_parse_entry_nlst (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_parse_entry(URLContext *h, char *line, AVIODirEntry *next)
{
    FTPContext *s = h->priv_data;

    switch (s->listing_method) {
    case MLSD:
        return ftp_parse_entry_mlsd(line, next);
    case NLST:
        return ftp_parse_entry_nlst(line, next);
    case UNKNOWN_METHOD:
    default:
        return -1;
    }
}