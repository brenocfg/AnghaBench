#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int unichar ;
struct bin_messagetable_item {scalar_t__ data; scalar_t__ flags; scalar_t__ length; } ;
typedef  int rc_uint_type ;
struct TYPE_7__ {int* message; TYPE_2__* lang; } ;
typedef  TYPE_3__ mc_node_lang ;
struct TYPE_5__ {int /*<<< orphan*/  wincp; } ;
struct TYPE_6__ {TYPE_1__ lang_info; } ;

/* Variables and functions */
 int BIN_MESSAGETABLE_ITEM_SIZE ; 
 int MESSAGE_RESOURCE_UNICODE ; 
 int /*<<< orphan*/  codepage_from_unicode (int*,int*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ mcset_automatic_null_termination ; 
 int mcset_bin_out_is_unicode ; 
 int /*<<< orphan*/  memset (struct bin_messagetable_item*,int /*<<< orphan*/ ,int) ; 
 struct bin_messagetable_item* res_alloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  target_put_16 (scalar_t__,int) ; 
 int unichar_len (int*) ; 

__attribute__((used)) static struct bin_messagetable_item *
mc_generate_bin_item (mc_node_lang *n, rc_uint_type *res_len)
{
  struct bin_messagetable_item *ret = NULL;
  rc_uint_type len;

  *res_len = 0;
  if (mcset_bin_out_is_unicode == 1)
    {
      unichar *ht = n->message;
      rc_uint_type txt_len;

      txt_len = unichar_len (n->message);
      if (mcset_automatic_null_termination && txt_len != 0)
	{
	  while (txt_len > 0 && ht[txt_len - 1] > 0 && ht[txt_len - 1] < 0x20)
	    ht[--txt_len] = 0;
	}
      txt_len *= sizeof (unichar);
      len = BIN_MESSAGETABLE_ITEM_SIZE + txt_len + sizeof (unichar);
      ret = res_alloc ((len + 3) & ~3);
      memset (ret, 0, (len + 3) & ~3);
      target_put_16 (ret->length, (len + 3) & ~3);
      target_put_16 (ret->flags, MESSAGE_RESOURCE_UNICODE);
      txt_len = 0;
      while (*ht != 0)
	{
	  target_put_16 (ret->data + txt_len, *ht++);
	  txt_len += 2;
	}
    }
  else
    {
      rc_uint_type txt_len, l;
      char *cvt_txt;

      codepage_from_unicode( &l, n->message, &cvt_txt, n->lang->lang_info.wincp);
      if (! cvt_txt)
	fatal ("Failed to convert message to language codepage.\n");
      txt_len = strlen (cvt_txt);
      if (mcset_automatic_null_termination && txt_len > 0)
	{
	  while (txt_len > 0 && cvt_txt[txt_len - 1] > 0 && cvt_txt[txt_len - 1] < 0x20)
	    cvt_txt[--txt_len] = 0;
	}
      len = BIN_MESSAGETABLE_ITEM_SIZE + txt_len + 1;
      ret = res_alloc ((len + 3) & ~3);
      memset (ret, 0, (len + 3) & ~3);
      target_put_16 (ret->length, (len + 3) & ~3);
      target_put_16 (ret->flags, 0);
      strcpy ((char *) ret->data, cvt_txt);
    }
  *res_len = (len + 3) & ~3;
  return ret;
}