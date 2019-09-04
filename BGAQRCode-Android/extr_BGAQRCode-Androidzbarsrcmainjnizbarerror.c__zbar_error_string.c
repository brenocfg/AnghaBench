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
struct TYPE_2__ {scalar_t__ magic; int sev; size_t module; char* func; size_t type; char const* buf; char const* detail; char const* arg_str; int /*<<< orphan*/  arg_int; } ;
typedef  TYPE_1__ errinfo_t ;
typedef  int /*<<< orphan*/  basefmt ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 int ERR_MAX ; 
 int MOD_MAX ; 
 int SEV_FATAL ; 
 int SEV_MAX ; 
 int SEV_NOTE ; 
 size_t ZBAR_ERR_NUM ; 
 size_t ZBAR_MOD_PROCESSOR ; 
 size_t ZBAR_MOD_UNKNOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 char** err_str ; 
 char** mod_str ; 
 void* realloc (char const*,int) ; 
 char** sev_str ; 
 int sprintf (char const*,char const*,...) ; 
 char const* strdup (char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

const char *_zbar_error_string (const void *container,
                                int verbosity)
{
    static const char basefmt[] = "%s: zbar %s in %s():\n    %s: ";
    errinfo_t *err = (errinfo_t*)container;
    const char *sev, *mod, *func, *type;
    int len;

    assert(err->magic == ERRINFO_MAGIC);

    if(err->sev >= SEV_FATAL && err->sev <= SEV_NOTE)
        sev = sev_str[err->sev + 2];
    else
        sev = sev_str[1];

    if(err->module >= ZBAR_MOD_PROCESSOR &&
       err->module < ZBAR_MOD_UNKNOWN)
        mod = mod_str[err->module];
    else
        mod = mod_str[ZBAR_MOD_UNKNOWN];

    func = (err->func) ? err->func : "<unknown>";

    if(err->type >= 0 && err->type < ZBAR_ERR_NUM)
        type = err_str[err->type];
    else
        type = err_str[ZBAR_ERR_NUM];

    len = SEV_MAX + MOD_MAX + ERR_MAX + strlen(func) + sizeof(basefmt);
    err->buf = realloc(err->buf, len);
    len = sprintf(err->buf, basefmt, sev, mod, func, type);
    if(len <= 0)
        return("<unknown>");

    if(err->detail) {
        int newlen = len + strlen(err->detail) + 1;
        if(strstr(err->detail, "%s")) {
            if(!err->arg_str)
                err->arg_str = strdup("<?>");
            err->buf = realloc(err->buf, newlen + strlen(err->arg_str));
            len += sprintf(err->buf + len, err->detail, err->arg_str);
        }
        else if(strstr(err->detail, "%d") || strstr(err->detail, "%x")) {
            err->buf = realloc(err->buf, newlen + 32);
            len += sprintf(err->buf + len, err->detail, err->arg_int);
        }
        else {
            err->buf = realloc(err->buf, newlen);
            len += sprintf(err->buf + len, "%s", err->detail);
        }
        if(len <= 0)
            return("<unknown>");
    }

#ifdef HAVE_ERRNO_H
    if(err->type == ZBAR_ERR_SYSTEM) {
        static const char sysfmt[] = ": %s (%d)\n";
        const char *syserr = strerror(err->errnum);
        err->buf = realloc(err->buf, len + strlen(sysfmt) + strlen(syserr));
        len += sprintf(err->buf + len, sysfmt, syserr, err->errnum);
    }
#endif
#ifdef _WIN32
    else if(err->type == ZBAR_ERR_WINAPI) {
        char *syserr = NULL;
        if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                         FORMAT_MESSAGE_ALLOCATE_BUFFER |
                         FORMAT_MESSAGE_IGNORE_INSERTS,
                         NULL, err->errnum, 0, (LPTSTR)&syserr, 1, NULL) &&
           syserr) {
            char sysfmt[] = ": %s (%d)\n";
            err->buf = realloc(err->buf, len + strlen(sysfmt) + strlen(syserr));
            len += sprintf(err->buf + len, sysfmt, syserr, err->errnum);
            LocalFree(syserr);
        }
    }
#endif
    else {
        err->buf = realloc(err->buf, len + 2);
        len += sprintf(err->buf + len, "\n");
    }
    return(err->buf);
}