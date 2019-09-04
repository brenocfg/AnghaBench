#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int type; int flags; char* help; scalar_t__ unit; } ;
typedef  TYPE_1__ AVOption ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int AV_OPT_FLAG_ENCODING_PARAM ; 
#define  FF_OPT_TYPE_BINARY 135 
 scalar_t__ FF_OPT_TYPE_CONST ; 
#define  FF_OPT_TYPE_DOUBLE 134 
#define  FF_OPT_TYPE_FLAGS 133 
#define  FF_OPT_TYPE_FLOAT 132 
#define  FF_OPT_TYPE_INT 131 
#define  FF_OPT_TYPE_INT64 130 
#define  FF_OPT_TYPE_RATIONAL 129 
#define  FF_OPT_TYPE_STRING 128 
 TYPE_1__* av_next_option (int /*<<< orphan*/  const**,TYPE_1__ const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void print_option(const AVClass *class, const AVOption *o)
{
    printf("@item -%s @var{", o->name);
    switch (o->type) {
    case FF_OPT_TYPE_BINARY:   printf("hexadecimal string"); break;
    case FF_OPT_TYPE_STRING:   printf("string");             break;
    case FF_OPT_TYPE_INT:
    case FF_OPT_TYPE_INT64:    printf("integer");            break;
    case FF_OPT_TYPE_FLOAT:
    case FF_OPT_TYPE_DOUBLE:   printf("float");              break;
    case FF_OPT_TYPE_RATIONAL: printf("rational number");    break;
    case FF_OPT_TYPE_FLAGS:    printf("flags");              break;
    default:                   printf("value");              break;
    }
    printf("} (@emph{");

    if (o->flags & AV_OPT_FLAG_ENCODING_PARAM) {
        printf("input");
        if (o->flags & AV_OPT_FLAG_ENCODING_PARAM)
            printf("/");
    }
    if (o->flags & AV_OPT_FLAG_ENCODING_PARAM)
        printf("output");

    printf("})\n");
    if (o->help)
        printf("%s\n", o->help);

    if (o->unit) {
        const AVOption *u = NULL;
        printf("\nPossible values:\n@table @samp\n");

        while ((u = av_next_option(&class, u)))
            if (u->type == FF_OPT_TYPE_CONST && u->unit && !strcmp(u->unit, o->unit))
                printf("@item %s\n%s\n", u->name, u->help ? u->help : "");
        printf("@end table\n");
    }
}