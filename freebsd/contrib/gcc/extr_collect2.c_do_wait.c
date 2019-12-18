__attribute__((used)) static void
do_wait (const char *prog, struct pex_obj *pex)
{
  int ret = collect_wait (prog, pex);
  if (ret != 0)
    {
      error ("%s returned %d exit status", prog, ret);
      collect_exit (ret);
    }
}