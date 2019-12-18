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
struct TYPE_3__ {int /*<<< orphan*/  (* end ) (void*) ;int /*<<< orphan*/  (* text ) (void*,char const*,int) ;int /*<<< orphan*/  (* origin ) (void*,int,int) ;int /*<<< orphan*/  (* move ) (void*,int,int,int,int,int,int) ;int /*<<< orphan*/  (* cancel_overrides ) (void*,char*) ;int /*<<< orphan*/  (* alignment ) (void*,int) ;int /*<<< orphan*/  (* font_size ) (void*,int) ;int /*<<< orphan*/  (* font_name ) (void*,char*) ;int /*<<< orphan*/  (* alpha ) (void*,int,char) ;int /*<<< orphan*/  (* color ) (void*,unsigned int,char) ;int /*<<< orphan*/  (* style ) (void*,char,int) ;int /*<<< orphan*/  (* new_line ) (void*,int) ;} ;
typedef  TYPE_1__ ASSCodesCallbacks ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int sscanf (char const*,char*,...) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (void*,char const*,int) ; 
 int /*<<< orphan*/  stub10 (void*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub11 (void*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub12 (void*,int,int) ; 
 int /*<<< orphan*/  stub13 (void*,char const*,int) ; 
 int /*<<< orphan*/  stub14 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,int) ; 
 int /*<<< orphan*/  stub3 (void*,char,int) ; 
 int /*<<< orphan*/  stub4 (void*,unsigned int,char) ; 
 int /*<<< orphan*/  stub5 (void*,int,char) ; 
 int /*<<< orphan*/  stub6 (void*,char*) ; 
 int /*<<< orphan*/  stub7 (void*,int) ; 
 int /*<<< orphan*/  stub8 (void*,int) ; 
 int /*<<< orphan*/  stub9 (void*,char*) ; 

int ff_ass_split_override_codes(const ASSCodesCallbacks *callbacks, void *priv,
                                const char *buf)
{
    const char *text = NULL;
    char new_line[2];
    int text_len = 0;

    while (buf && *buf) {
        if (text && callbacks->text &&
            (sscanf(buf, "\\%1[nN]", new_line) == 1 ||
             !strncmp(buf, "{\\", 2))) {
            callbacks->text(priv, text, text_len);
            text = NULL;
        }
        if (sscanf(buf, "\\%1[nN]", new_line) == 1) {
            if (callbacks->new_line)
                callbacks->new_line(priv, new_line[0] == 'N');
            buf += 2;
        } else if (!strncmp(buf, "{\\", 2)) {
            buf++;
            while (*buf == '\\') {
                char style[2], c[2], sep[2], c_num[2] = "0", tmp[128] = {0};
                unsigned int color = 0xFFFFFFFF;
                int len, size = -1, an = -1, alpha = -1;
                int x1, y1, x2, y2, t1 = -1, t2 = -1;
                if (sscanf(buf, "\\%1[bisu]%1[01\\}]%n", style, c, &len) > 1) {
                    int close = c[0] == '0' ? 1 : c[0] == '1' ? 0 : -1;
                    len += close != -1;
                    if (callbacks->style)
                        callbacks->style(priv, style[0], close);
                } else if (sscanf(buf, "\\c%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\c&H%X&%1[\\}]%n", &color, sep, &len) > 1 ||
                           sscanf(buf, "\\%1[1234]c%1[\\}]%n", c_num, sep, &len) > 1 ||
                           sscanf(buf, "\\%1[1234]c&H%X&%1[\\}]%n", c_num, &color, sep, &len) > 2) {
                    if (callbacks->color)
                        callbacks->color(priv, color, c_num[0] - '0');
                } else if (sscanf(buf, "\\alpha%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\alpha&H%2X&%1[\\}]%n", &alpha, sep, &len) > 1 ||
                           sscanf(buf, "\\%1[1234]a%1[\\}]%n", c_num, sep, &len) > 1 ||
                           sscanf(buf, "\\%1[1234]a&H%2X&%1[\\}]%n", c_num, &alpha, sep, &len) > 2) {
                    if (callbacks->alpha)
                        callbacks->alpha(priv, alpha, c_num[0] - '0');
                } else if (sscanf(buf, "\\fn%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\fn%127[^\\}]%1[\\}]%n", tmp, sep, &len) > 1) {
                    if (callbacks->font_name)
                        callbacks->font_name(priv, tmp[0] ? tmp : NULL);
                } else if (sscanf(buf, "\\fs%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\fs%u%1[\\}]%n", &size, sep, &len) > 1) {
                    if (callbacks->font_size)
                        callbacks->font_size(priv, size);
                } else if (sscanf(buf, "\\a%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\a%2u%1[\\}]%n", &an, sep, &len) > 1 ||
                           sscanf(buf, "\\an%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\an%1u%1[\\}]%n", &an, sep, &len) > 1) {
                    if (an != -1 && buf[2] != 'n')
                        an = (an&3) + (an&4 ? 6 : an&8 ? 3 : 0);
                    if (callbacks->alignment)
                        callbacks->alignment(priv, an);
                } else if (sscanf(buf, "\\r%1[\\}]%n", sep, &len) > 0 ||
                           sscanf(buf, "\\r%127[^\\}]%1[\\}]%n", tmp, sep, &len) > 1) {
                    if (callbacks->cancel_overrides)
                        callbacks->cancel_overrides(priv, tmp);
                } else if (sscanf(buf, "\\move(%d,%d,%d,%d)%1[\\}]%n", &x1, &y1, &x2, &y2, sep, &len) > 4 ||
                           sscanf(buf, "\\move(%d,%d,%d,%d,%d,%d)%1[\\}]%n", &x1, &y1, &x2, &y2, &t1, &t2, sep, &len) > 6) {
                    if (callbacks->move)
                        callbacks->move(priv, x1, y1, x2, y2, t1, t2);
                } else if (sscanf(buf, "\\pos(%d,%d)%1[\\}]%n", &x1, &y1, sep, &len) > 2) {
                    if (callbacks->move)
                        callbacks->move(priv, x1, y1, x1, y1, -1, -1);
                } else if (sscanf(buf, "\\org(%d,%d)%1[\\}]%n", &x1, &y1, sep, &len) > 2) {
                    if (callbacks->origin)
                        callbacks->origin(priv, x1, y1);
                } else {
                    len = strcspn(buf+1, "\\}") + 2;  /* skip unknown code */
                }
                buf += len - 1;
            }
            if (*buf++ != '}')
                return AVERROR_INVALIDDATA;
        } else {
            if (!text) {
                text = buf;
                text_len = 1;
            } else
                text_len++;
            buf++;
        }
    }
    if (text && callbacks->text)
        callbacks->text(priv, text, text_len);
    if (callbacks->end)
        callbacks->end(priv);
    return 0;
}