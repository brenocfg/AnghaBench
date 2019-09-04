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
typedef  char* sds ;
struct TYPE_4__ {int type; char* str; int len; size_t elements; struct TYPE_4__** element; int /*<<< orphan*/  integer; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_5__ {int /*<<< orphan*/  mb_delim; } ;

/* Variables and functions */
#define  REDIS_REPLY_ARRAY 133 
#define  REDIS_REPLY_ERROR 132 
#define  REDIS_REPLY_INTEGER 131 
#define  REDIS_REPLY_NIL 130 
#define  REDIS_REPLY_STATUS 129 
#define  REDIS_REPLY_STRING 128 
 TYPE_2__ config ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* sdscat (char*,int /*<<< orphan*/ ) ; 
 char* sdscatlen (char*,char*,int) ; 
 char* sdscatprintf (char*,char*,int /*<<< orphan*/ ) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static sds cliFormatReplyRaw(redisReply *r) {
    sds out = sdsempty(), tmp;
    size_t i;

    switch (r->type) {
    case REDIS_REPLY_NIL:
        /* Nothing... */
        break;
    case REDIS_REPLY_ERROR:
        out = sdscatlen(out,r->str,r->len);
        out = sdscatlen(out,"\n",1);
        break;
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_STRING:
        out = sdscatlen(out,r->str,r->len);
        break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"%lld",r->integer);
        break;
    case REDIS_REPLY_ARRAY:
        for (i = 0; i < r->elements; i++) {
            if (i > 0) out = sdscat(out,config.mb_delim);
            tmp = cliFormatReplyRaw(r->element[i]);
            out = sdscatlen(out,tmp,sdslen(tmp));
            sdsfree(tmp);
        }
        break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}