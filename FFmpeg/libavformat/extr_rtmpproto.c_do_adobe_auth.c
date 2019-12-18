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
typedef  int /*<<< orphan*/  uint8_t ;
struct AVMD5 {int dummy; } ;
typedef  int /*<<< orphan*/  hashstr ;
typedef  int /*<<< orphan*/  hash ;
typedef  int /*<<< orphan*/  challenge2 ;
struct TYPE_3__ {char* password; int /*<<< orphan*/  auth_params; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_BASE64_SIZE (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_base64_encode (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_free (struct AVMD5*) ; 
 int av_get_random_seed () ; 
 struct AVMD5* av_md5_alloc () ; 
 int /*<<< orphan*/  av_md5_final (struct AVMD5*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_md5_init (struct AVMD5*) ; 
 int /*<<< orphan*/  av_md5_update (struct AVMD5*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcatf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int do_adobe_auth(RTMPContext *rt, const char *user, const char *salt,
                         const char *opaque, const char *challenge)
{
    uint8_t hash[16];
    char hashstr[AV_BASE64_SIZE(sizeof(hash))], challenge2[10];
    struct AVMD5 *md5 = av_md5_alloc();
    if (!md5)
        return AVERROR(ENOMEM);

    snprintf(challenge2, sizeof(challenge2), "%08x", av_get_random_seed());

    av_md5_init(md5);
    av_md5_update(md5, user, strlen(user));
    av_md5_update(md5, salt, strlen(salt));
    av_md5_update(md5, rt->password, strlen(rt->password));
    av_md5_final(md5, hash);
    av_base64_encode(hashstr, sizeof(hashstr), hash,
                     sizeof(hash));
    av_md5_init(md5);
    av_md5_update(md5, hashstr, strlen(hashstr));
    if (opaque)
        av_md5_update(md5, opaque, strlen(opaque));
    else if (challenge)
        av_md5_update(md5, challenge, strlen(challenge));
    av_md5_update(md5, challenge2, strlen(challenge2));
    av_md5_final(md5, hash);
    av_base64_encode(hashstr, sizeof(hashstr), hash,
                     sizeof(hash));
    snprintf(rt->auth_params, sizeof(rt->auth_params),
             "?authmod=%s&user=%s&challenge=%s&response=%s",
             "adobe", user, challenge2, hashstr);
    if (opaque)
        av_strlcatf(rt->auth_params, sizeof(rt->auth_params),
                    "&opaque=%s", opaque);

    av_free(md5);
    return 0;
}