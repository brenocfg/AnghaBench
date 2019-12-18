#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct exception_context {int dummy; } ;
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structp ;
struct TYPE_10__ {int noptions; int /*<<< orphan*/ * pread; int /*<<< orphan*/  piread; TYPE_1__* options; struct exception_context exception_context; int /*<<< orphan*/  read_memory_pool; int /*<<< orphan*/  speed; int /*<<< orphan*/  test; } ;
typedef  TYPE_2__ png_store ;
typedef  int /*<<< orphan*/ * png_infopp ;
typedef  int /*<<< orphan*/  Throw ;
struct TYPE_9__ {int /*<<< orphan*/  setting; int /*<<< orphan*/  option; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 scalar_t__ PNG_OPTION_INVALID ; 
 int /*<<< orphan*/  png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * png_create_read_struct_2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ png_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safecat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  store_error ; 
 int /*<<< orphan*/  store_free ; 
 int /*<<< orphan*/  store_log (TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  store_malloc ; 
 int /*<<< orphan*/  store_read_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  store_read_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_warning ; 

__attribute__((used)) static png_structp
set_store_for_read(png_store *ps, png_infopp ppi, png_uint_32 id,
   const char *name)
{
   /* Set the name for png_error */
   safecat(ps->test, sizeof ps->test, 0, name);

   if (ps->pread != NULL)
      png_error(ps->pread, "read store already in use");

   store_read_reset(ps);

   /* Both the create APIs can return NULL if used in their default mode
    * (because there is no other way of handling an error because the jmp_buf
    * by default is stored in png_struct and that has not been allocated!)
    * However, given that store_error works correctly in these circumstances
    * we don't ever expect NULL in this program.
    */
#  ifdef PNG_USER_MEM_SUPPORTED
      if (!ps->speed)
         ps->pread = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, ps,
             store_error, store_warning, &ps->read_memory_pool, store_malloc,
             store_free);

      else
#  endif
   ps->pread = png_create_read_struct(PNG_LIBPNG_VER_STRING, ps, store_error,
      store_warning);

   if (ps->pread == NULL)
   {
      struct exception_context *the_exception_context = &ps->exception_context;

      store_log(ps, NULL, "png_create_read_struct returned NULL (unexpected)",
         1 /*error*/);

      Throw ps;
   }

#  ifdef PNG_SET_OPTION_SUPPORTED
      {
         int opt;
         for (opt=0; opt<ps->noptions; ++opt)
            if (png_set_option(ps->pread, ps->options[opt].option,
               ps->options[opt].setting) == PNG_OPTION_INVALID)
                  png_error(ps->pread, "png option invalid");
      }
#  endif

   store_read_set(ps, id);

   if (ppi != NULL)
      *ppi = ps->piread = png_create_info_struct(ps->pread);

   return ps->pread;
}