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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_1__ URLContext ;
typedef  int /*<<< orphan*/  SecExternalFormat ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  int /*<<< orphan*/ * CFDataRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 scalar_t__ AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 scalar_t__ CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CFDataCreate (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SecItemImport (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_read (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ *) ; 
 scalar_t__ ffio_open_whitelist (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kSecFormatPEMSequence ; 
 int /*<<< orphan*/  kSecItemTypeAggregate ; 
 scalar_t__ noErr ; 

__attribute__((used)) static int import_pem(URLContext *h, char *path, CFArrayRef *array)
{
#if !HAVE_SECITEMIMPORT
    return AVERROR_PATCHWELCOME;
#else
    AVIOContext *s = NULL;
    CFDataRef data = NULL;
    int64_t ret = 0;
    char *buf = NULL;
    SecExternalFormat format = kSecFormatPEMSequence;
    SecExternalFormat type = kSecItemTypeAggregate;
    CFStringRef pathStr = CFStringCreateWithCString(NULL, path, 0x08000100);
    if (!pathStr) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    if ((ret = ffio_open_whitelist(&s, path, AVIO_FLAG_READ,
                                   &h->interrupt_callback, NULL,
                                   h->protocol_whitelist, h->protocol_blacklist)) < 0)
        goto end;

    if ((ret = avio_size(s)) < 0)
        goto end;

    if (ret == 0) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }

    if (!(buf = av_malloc(ret))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    if ((ret = avio_read(s, buf, ret)) < 0)
        goto end;

    data = CFDataCreate(kCFAllocatorDefault, buf, ret);

    if (SecItemImport(data, pathStr, &format, &type,
                      0, NULL, NULL, array) != noErr || !array) {
        ret = AVERROR_UNKNOWN;
        goto end;
    }

    if (CFArrayGetCount(*array) == 0) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }

end:
    av_free(buf);
    if (pathStr)
        CFRelease(pathStr);
    if (data)
        CFRelease(data);
    if (s)
        avio_close(s);
    return ret;
#endif
}