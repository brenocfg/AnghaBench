#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tm ;
struct tm {int dummy; } ;
struct TYPE_2__ {char* shortopts; char* longopts; char* datatype; } ;
struct arg_date {int /*<<< orphan*/  format; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  EBADDATE 130 
#define  EMAXCOUNT 129 
#define  EMINCOUNT 128 
 int /*<<< orphan*/  arg_print_option (int /*<<< orphan*/ *,char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  arg_strptime (char*,char*,struct tm*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void arg_date_errorfn(
    struct arg_date *parent,
    FILE *fp,
    int errorcode,
    const char *argval,
    const char *progname)
{
    const char *shortopts = parent->hdr.shortopts;
    const char *longopts  = parent->hdr.longopts;
    const char *datatype  = parent->hdr.datatype;

    /* make argval NULL safe */
    argval = argval ? argval : "";

    fprintf(fp, "%s: ", progname);
    switch(errorcode)
    {
    case EMINCOUNT:
        fputs("missing option ", fp);
        arg_print_option(fp, shortopts, longopts, datatype, "\n");
        break;

    case EMAXCOUNT:
        fputs("excess option ", fp);
        arg_print_option(fp, shortopts, longopts, argval, "\n");
        break;

    case EBADDATE:
    {
        struct tm tm;
        char buff[200];

        fprintf(fp, "illegal timestamp format \"%s\"\n", argval);
        memset(&tm, 0, sizeof(tm));
        arg_strptime("1999-12-31 23:59:59", "%F %H:%M:%S", &tm);
        strftime(buff, sizeof(buff), parent->format, &tm);
        printf("correct format is \"%s\"\n", buff);
        break;
    }
    }
}