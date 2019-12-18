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
typedef  int /*<<< orphan*/  tree ;
typedef  enum tls_model { ____Placeholder_tls_model } tls_model ;
struct TYPE_2__ {int (* binds_local_p ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int TLS_MODEL_GLOBAL_DYNAMIC ; 
 int TLS_MODEL_INITIAL_EXEC ; 
 int TLS_MODEL_LOCAL_DYNAMIC ; 
 int TLS_MODEL_LOCAL_EXEC ; 
 int /*<<< orphan*/  flag_shlib ; 
 int flag_tls_default ; 
 scalar_t__ optimize ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 

enum tls_model
decl_default_tls_model (tree decl)
{
  enum tls_model kind;
  bool is_local;

  is_local = targetm.binds_local_p (decl);
  if (!flag_shlib)
    {
      if (is_local)
	kind = TLS_MODEL_LOCAL_EXEC;
      else
	kind = TLS_MODEL_INITIAL_EXEC;
    }

  /* Local dynamic is inefficient when we're not combining the
     parts of the address.  */
  else if (optimize && is_local)
    kind = TLS_MODEL_LOCAL_DYNAMIC;
  else
    kind = TLS_MODEL_GLOBAL_DYNAMIC;
  if (kind < flag_tls_default)
    kind = flag_tls_default;

  return kind;
}