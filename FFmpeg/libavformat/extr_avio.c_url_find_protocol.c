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
struct URLProtocol {int flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  proto_str ;
typedef  int /*<<< orphan*/  proto_nested ;
typedef  struct URLProtocol URLProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFMIN (size_t,int) ; 
 int URL_PROTOCOL_FLAG_NESTED_SCHEME ; 
 int /*<<< orphan*/  URL_SCHEME_CHARS ; 
 int /*<<< orphan*/  av_freep (struct URLProtocol const***) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 scalar_t__ av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 struct URLProtocol** ffurl_get_protocols (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_dos_path (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 size_t strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct URLProtocol *url_find_protocol(const char *filename)
{
    const URLProtocol **protocols;
    char proto_str[128], proto_nested[128], *ptr;
    size_t proto_len = strspn(filename, URL_SCHEME_CHARS);
    int i;

    if (filename[proto_len] != ':' &&
        (strncmp(filename, "subfile,", 8) || !strchr(filename + proto_len + 1, ':')) ||
        is_dos_path(filename))
        strcpy(proto_str, "file");
    else
        av_strlcpy(proto_str, filename,
                   FFMIN(proto_len + 1, sizeof(proto_str)));

    av_strlcpy(proto_nested, proto_str, sizeof(proto_nested));
    if ((ptr = strchr(proto_nested, '+')))
        *ptr = '\0';

    protocols = ffurl_get_protocols(NULL, NULL);
    if (!protocols)
        return NULL;
    for (i = 0; protocols[i]; i++) {
            const URLProtocol *up = protocols[i];
        if (!strcmp(proto_str, up->name)) {
            av_freep(&protocols);
            return up;
        }
        if (up->flags & URL_PROTOCOL_FLAG_NESTED_SCHEME &&
            !strcmp(proto_nested, up->name)) {
            av_freep(&protocols);
            return up;
        }
    }
    av_freep(&protocols);
    if (av_strstart(filename, "https:", NULL) || av_strstart(filename, "tls:", NULL))
        av_log(NULL, AV_LOG_WARNING, "https protocol not found, recompile FFmpeg with "
                                     "openssl, gnutls or securetransport enabled.\n");

    return NULL;
}