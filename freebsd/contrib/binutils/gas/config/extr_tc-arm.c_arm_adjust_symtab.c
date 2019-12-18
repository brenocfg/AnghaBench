void
arm_adjust_symtab (void)
{
#ifdef OBJ_COFF
  symbolS * sym;

  for (sym = symbol_rootP; sym != NULL; sym = symbol_next (sym))
    {
      if (ARM_IS_THUMB (sym))
	{
	  if (THUMB_IS_FUNC (sym))
	    {
	      /* Mark the symbol as a Thumb function.  */
	      if (   S_GET_STORAGE_CLASS (sym) == C_STAT
		  || S_GET_STORAGE_CLASS (sym) == C_LABEL)  /* This can happen!	 */
		S_SET_STORAGE_CLASS (sym, C_THUMBSTATFUNC);

	      else if (S_GET_STORAGE_CLASS (sym) == C_EXT)
		S_SET_STORAGE_CLASS (sym, C_THUMBEXTFUNC);
	      else
		as_bad (_("%s: unexpected function type: %d"),
			S_GET_NAME (sym), S_GET_STORAGE_CLASS (sym));
	    }
	  else switch (S_GET_STORAGE_CLASS (sym))
	    {
	    case C_EXT:
	      S_SET_STORAGE_CLASS (sym, C_THUMBEXT);
	      break;
	    case C_STAT:
	      S_SET_STORAGE_CLASS (sym, C_THUMBSTAT);
	      break;
	    case C_LABEL:
	      S_SET_STORAGE_CLASS (sym, C_THUMBLABEL);
	      break;
	    default:
	      /* Do nothing.  */
	      break;
	    }
	}

      if (ARM_IS_INTERWORK (sym))
	coffsymbol (symbol_get_bfdsym (sym))->native->u.syment.n_flags = 0xFF;
    }
#endif
#ifdef OBJ_ELF
  symbolS * sym;
  char	    bind;

  for (sym = symbol_rootP; sym != NULL; sym = symbol_next (sym))
    {
      if (ARM_IS_THUMB (sym))
	{
	  elf_symbol_type * elf_sym;

	  elf_sym = elf_symbol (symbol_get_bfdsym (sym));
	  bind = ELF_ST_BIND (elf_sym->internal_elf_sym.st_info);

	  if (! bfd_is_arm_special_symbol_name (elf_sym->symbol.name,
		BFD_ARM_SPECIAL_SYM_TYPE_ANY))
	    {
	      /* If it's a .thumb_func, declare it as so,
		 otherwise tag label as .code 16.  */
	      if (THUMB_IS_FUNC (sym))
		elf_sym->internal_elf_sym.st_info =
		  ELF_ST_INFO (bind, STT_ARM_TFUNC);
	      else if (EF_ARM_EABI_VERSION (meabi_flags) < EF_ARM_EABI_VER4)
		elf_sym->internal_elf_sym.st_info =
		  ELF_ST_INFO (bind, STT_ARM_16BIT);
	    }
	}
    }
#endif
}