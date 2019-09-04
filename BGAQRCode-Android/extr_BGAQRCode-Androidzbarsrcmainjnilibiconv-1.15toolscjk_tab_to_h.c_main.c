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

/* Variables and functions */
 int /*<<< orphan*/  do_big5 (char const*) ; 
 int /*<<< orphan*/  do_cns11643_only_uni2charset (char const*) ; 
 int /*<<< orphan*/  do_gb18030uni (char const*) ; 
 int /*<<< orphan*/  do_gbk1 (char const*) ; 
 int /*<<< orphan*/  do_gbk1_only_charset2uni (char const*) ; 
 int /*<<< orphan*/  do_gbk1_only_uni2charset (char const*) ; 
 int /*<<< orphan*/  do_gbk2_only_charset2uni (char const*) ; 
 int /*<<< orphan*/  do_hkscs (char const*) ; 
 int /*<<< orphan*/  do_jisx0213 (char const*) ; 
 int /*<<< orphan*/  do_johab_hangul (char const*) ; 
 int /*<<< orphan*/  do_ksc5601 (char const*) ; 
 int /*<<< orphan*/  do_normal (char const*) ; 
 int /*<<< orphan*/  do_normal_only_charset2uni (char const*) ; 
 int /*<<< orphan*/  do_sjis (char const*) ; 
 int /*<<< orphan*/  do_uhc_1 (char const*) ; 
 int /*<<< orphan*/  do_uhc_2 (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  output_title (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main (int argc, char *argv[])
{
  const char* charsetname;
  const char* name;

  if (argc != 3)
    exit(1);
  charsetname = argv[1];
  name = argv[2];

  output_title(charsetname);

  if (!strcmp(name,"gb2312")
      || !strcmp(name,"isoir165ext") || !strcmp(name,"gb12345ext")
      || !strcmp(name,"jisx0208") || !strcmp(name,"jisx0212"))
    do_normal(name);
  else if (!strcmp(name,"cns11643_1") || !strcmp(name,"cns11643_2")
           || !strcmp(name,"cns11643_3") || !strcmp(name,"cns11643_4a")
           || !strcmp(name,"cns11643_4b") || !strcmp(name,"cns11643_5")
           || !strcmp(name,"cns11643_6") || !strcmp(name,"cns11643_7")
           || !strcmp(name,"cns11643_15"))
    do_normal_only_charset2uni(name);
  else if (!strcmp(name,"cns11643_inv"))
    do_cns11643_only_uni2charset(name);
  else if (!strcmp(name,"gbkext1"))
    do_gbk1_only_charset2uni(name);
  else if (!strcmp(name,"gbkext2"))
    do_gbk2_only_charset2uni(name);
  else if (!strcmp(name,"gbkext_inv"))
    do_gbk1_only_uni2charset(name);
  else if (!strcmp(name,"cp936ext") || !strcmp(name,"gb18030ext"))
    do_gbk1(name);
  else if (!strcmp(name,"ksc5601"))
    do_ksc5601(name);
  else if (!strcmp(name,"uhc_1"))
    do_uhc_1(name);
  else if (!strcmp(name,"uhc_2"))
    do_uhc_2(name);
  else if (!strcmp(name,"big5") || !strcmp(name,"cp950ext"))
    do_big5(name);
  else if (!strcmp(name,"hkscs1999") || !strcmp(name,"hkscs2001")
           || !strcmp(name,"hkscs2004") || !strcmp(name,"hkscs2008"))
    do_hkscs(name);
  else if (!strcmp(name,"johab_hangul"))
    do_johab_hangul(name);
  else if (!strcmp(name,"cp932ext"))
    do_sjis(name);
  else if (!strcmp(name,"gb18030uni"))
    do_gb18030uni(name);
  else if (!strcmp(name,"jisx0213"))
    do_jisx0213(name);
  else
    exit(1);

  return 0;
}