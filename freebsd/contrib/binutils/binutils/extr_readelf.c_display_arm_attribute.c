#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tag; char* name; int type; char** table; } ;
typedef  TYPE_1__ arm_attr_public_tag ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* arm_attr_public_tags ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_uleb128 (unsigned char*,unsigned int*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static unsigned char *
display_arm_attribute (unsigned char *p)
{
  int tag;
  unsigned int len;
  int val;
  arm_attr_public_tag *attr;
  unsigned i;
  int type;

  tag = read_uleb128 (p, &len);
  p += len;
  attr = NULL;
  for (i = 0; i < ARRAY_SIZE(arm_attr_public_tags); i++)
    {
      if (arm_attr_public_tags[i].tag == tag)
	{
	  attr = &arm_attr_public_tags[i];
	  break;
	}
    }

  if (attr)
    {
      printf ("  Tag_%s: ", attr->name);
      switch (attr->type)
	{
	case 0:
	  switch (tag)
	    {
	    case 7: /* Tag_CPU_arch_profile.  */
	      val = read_uleb128 (p, &len);
	      p += len;
	      switch (val)
		{
		case 0: printf ("None\n"); break;
		case 'A': printf ("Application\n"); break;
		case 'R': printf ("Realtime\n"); break;
		case 'M': printf ("Microcontroller\n"); break;
		default: printf ("??? (%d)\n", val); break;
		}
	      break;

	    case 32: /* Tag_compatibility.  */
	      val = read_uleb128 (p, &len);
	      p += len;
	      printf ("flag = %d, vendor = %s\n", val, p);
	      p += strlen((char *)p) + 1;
	      break;

	    default:
	      abort();
	    }
	  return p;

	case 1:
	case 2:
	  type = attr->type;
	  break;

	default:
	  assert (attr->type & 0x80);
	  val = read_uleb128 (p, &len);
	  p += len;
	  type = attr->type & 0x7f;
	  if (val >= type)
	    printf ("??? (%d)\n", val);
	  else
	    printf ("%s\n", attr->table[val]);
	  return p;
	}
    }
  else
    {
      if (tag & 1)
	type = 1; /* String.  */
      else
	type = 2; /* uleb128.  */
      printf ("  Tag_unknown_%d: ", tag);
    }

  if (type == 1)
    {
      printf ("\"%s\"\n", p);
      p += strlen((char *)p) + 1;
    }
  else
    {
      val = read_uleb128 (p, &len);
      p += len;
      printf ("%d (0x%x)\n", val, val);
    }

  return p;
}