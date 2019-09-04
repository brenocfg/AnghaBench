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
typedef  char* sds ;
struct TYPE_3__ {int type; char* str; unsigned int elements; struct TYPE_3__** element; int /*<<< orphan*/  len; int /*<<< orphan*/  integer; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  _prefixfmt ;

/* Variables and functions */
#define  REDIS_REPLY_ARRAY 133 
#define  REDIS_REPLY_ERROR 132 
#define  REDIS_REPLY_INTEGER 131 
#define  REDIS_REPLY_NIL 130 
#define  REDIS_REPLY_STATUS 129 
#define  REDIS_REPLY_STRING 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,unsigned int) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatlen (char*,char*,int /*<<< orphan*/ ) ; 
 char* sdscatprintf (char*,char*,char*,...) ; 
 char* sdscatrepr (char*,char*,int /*<<< orphan*/ ) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdslen (char*) ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        out = sdscatprintf(out,"(error) %s\n", r->str);
    break;
    case REDIS_REPLY_STATUS:
        out = sdscat(out,r->str);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_INTEGER:
        out = sdscatprintf(out,"(integer) %lld\n",r->integer);
    break;
    case REDIS_REPLY_STRING:
        /* If you are producing output for the standard output we want
        * a more interesting output with quoted characters and so forth */
        out = sdscatrepr(out,r->str,r->len);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_NIL:
        out = sdscat(out,"(nil)\n");
    break;
    case REDIS_REPLY_ARRAY:
        if (r->elements == 0) {
            out = sdscat(out,"(empty list or set)\n");
        } else {
            unsigned int i, idxlen = 0;
            char _prefixlen[16];
            char _prefixfmt[16];
            sds _prefix;
            sds tmp;

            /* Calculate chars needed to represent the largest index */
            i = r->elements;
            do {
                idxlen++;
                i /= 10;
            } while(i);

            /* Prefix for nested multi bulks should grow with idxlen+2 spaces */
            memset(_prefixlen,' ',idxlen+2);
            _prefixlen[idxlen+2] = '\0';
            _prefix = sdscat(sdsnew(prefix),_prefixlen);

            /* Setup prefix format for every entry */
            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%ud) ",idxlen);

            for (i = 0; i < r->elements; i++) {
                /* Don't use the prefix for the first element, as the parent
                 * caller already prepended the index number. */
                out = sdscatprintf(out,_prefixfmt,i == 0 ? "" : prefix,i+1);

                /* Format the multi bulk entry */
                tmp = cliFormatReplyTTY(r->element[i],_prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);
            }
            sdsfree(_prefix);
        }
    break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}